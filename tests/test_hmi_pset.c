/* 模式3真实字节布局与独立接头执行；不将目标赋给反馈，不要求任意参数都成功。 */
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "../Simulation/native_pset.h"
static void put(uint8_t *p,uint32_t v){unsigned i;for(i=0;i<4;i++)p[i]=(uint8_t)(v>>(8*i));}
static void frame(uint8_t p[1539])
{
    uint8_t *s=p+3;memset(p,0,1539);p[0]=1;p[1]=3;p[2]=1;
    put(s,300);put(s+12,10000);s[20]=1;s[21]=3;s[22]=1;s[23]=2;
    put(s+28,11000);put(s+32,14000);put(s+36,10000);put(s+40,1000);
    put(s+48,20000);put(s+52,100000);put(s+56,30000);put(s+60,15000);
    put(s+72,1);put(s+76,1);put(s+80,1);
}
static void start(FpgaProgramRun *r,const FpgaProgram *p)
{FpgaProgram_Reset(r);assert(FpgaProgram_Load(r,p));assert(FpgaProgram_Start(r,0,1));}
static void test_step_reset(void)
{
    uint8_t bytes[1539],*second=bytes+99;
    FpgaProgram program;
    FpgaProgramRun reset,carry;
    unsigned t;
    frame(bytes);
    bytes[2]=2;
    memcpy(second,bytes+3,96);
    second[20]=2;
    put(second+24,1); /* 角度策略，接头由第一步真实拧紧。 */
    put(second+32,30000);put(second+36,0);put(second+40,0);put(second+60,1400);
    assert(NativePset_Decode(bytes,195,&program));
    start(&reset,&program);
    put(second+76,0);put(second+80,0);
    assert(NativePset_Decode(bytes,195,&program));
    assert(!program.steps[1].angle_reset&&!program.steps[1].torque_reset);
    start(&carry,&program);
    for(t=1;t<3000&&carry.current_step!=2;t++){
        FpgaProgram_Tick(&reset,t,1);FpgaProgram_Tick(&carry,t,1);
        assert(reset.position_inc==carry.position_inc&&reset.torque_raw==carry.torque_raw);
    }
    assert(t<3000&&reset.current_step==2&&reset.position_inc==0);
    assert(reset.process_angle_cdeg==0&&carry.process_angle_cdeg==1134);
    assert(reset.carried_torque_peak_mnm==0&&carry.carried_torque_peak_mnm==12420);
    for(;t<5000&&(reset.state==FPGA_SIM_RUNNING||carry.state==FPGA_SIM_RUNNING);t++){
        if(reset.state==FPGA_SIM_RUNNING)FpgaProgram_Tick(&reset,t,1);
        if(carry.state==FPGA_SIM_RUNNING)FpgaProgram_Tick(&carry,t,1);
    }
    assert(reset.result&&carry.result&&reset.state==FPGA_SIM_DONE&&carry.state==FPGA_SIM_DONE);
    assert(reset.measured_angle_cdeg>=1400&&carry.measured_angle_cdeg<500&&carry.process_angle_cdeg>=1400);
    /* 停车和重新启动后，工艺测量不会把上一颗的峰值和角度接进来。 */
    assert(FpgaProgram_Start(&carry,t,1));
    assert(carry.process_angle_cdeg==0&&carry.carried_torque_peak_mnm==0&&carry.position_inc==0);
}
static void test_step_entry_limit(void)
{
    uint8_t bytes[1539],*second=bytes+99;
    FpgaProgram program;
    FpgaProgramRun run;
    unsigned mode,t;
    frame(bytes);
    bytes[2]=2;
    memcpy(second,bytes+3,96);
    second[20]=2;second[22]=2;
    put(second+24,1);put(second+32,12300);put(second+36,0);put(second+40,0);put(second+60,200);
    for(mode=0;mode<2;mode++){
        put(second+56,mode?12300:30000);
        assert(NativePset_Decode(bytes,195,&program));
        start(&run,&program);
        for(t=1;t<3000&&run.current_step!=2;t++)FpgaProgram_Tick(&run,t,1);
        assert(t<3000&&run.measured_torque_mnm==12420&&run.velocity_inc_s==0&&run.position_inc==0);
        FpgaProgram_Tick(&run,t,1);
        assert(run.state==FPGA_SIM_FAULT&&run.fault_code==(mode?0x7005u:0x7007u)&&!run.result);
        assert(run.measured_torque_mnm==12420&&run.peak_torque_mnm==12420);
        assert(run.velocity_inc_s==0&&run.position_inc==0);
    }
}
int main(void)
{
    uint8_t bytes[1539];FpgaProgram p,old;FpgaProgramRun r;unsigned i;
    frame(bytes);assert(NativePset_Decode(bytes,99,&p));
    assert(p.steps[0].torque_mnm==11000&&p.steps[0].speed_rpm_milli==30000);
    start(&r,&p);for(i=1;i<10000&&r.state==FPGA_SIM_RUNNING;i++)FpgaProgram_Tick(&r,i,1);
    assert(r.state==FPGA_SIM_DONE&&r.result&&r.peak_torque_mnm==12420&&r.measured_angle_cdeg==1134);
    /* 提高速度而保持同一接头/窗口，应因真实模型过冲而故障，不能特判为OK。 */
    put(bytes+3,3000);assert(NativePset_Decode(bytes,99,&p));start(&r,&p);
    for(i=1;i<10000&&r.state==FPGA_SIM_RUNNING;i++)FpgaProgram_Tick(&r,i,1);
    assert(r.state==FPGA_SIM_FAULT&&r.fault_code==0x7007&&!r.result);
    /* 启动门槛取独立反馈。先到目标仍停止，不能靠过冲或写入反馈补成合格。 */
    frame(bytes);put(bytes+3+64,1000);assert(NativePset_Decode(bytes,99,&p));start(&r,&p);
    for(i=1;i<10000&&r.state==FPGA_SIM_RUNNING;i++)FpgaProgram_Tick(&r,i,1);
    assert(i==2077&&r.state==FPGA_SIM_DONE&&r.result&&r.peak_torque_mnm==12420&&r.measured_angle_cdeg==1134);
    put(bytes+3+64,12000);assert(NativePset_Decode(bytes,99,&p));start(&r,&p);
    for(i=1;i<10000&&r.state==FPGA_SIM_RUNNING;i++)FpgaProgram_Tick(&r,i,1);
    assert(i==2077&&r.state==FPGA_SIM_DONE&&!r.result&&r.peak_torque_mnm==12420&&r.measured_angle_cdeg==1134);
    put(bytes+3+64,11000);assert(NativePset_Decode(bytes,99,&p));start(&r,&p);
    for(i=1;i<10000&&r.state==FPGA_SIM_RUNNING;i++)FpgaProgram_Tick(&r,i,1);
    assert(i==2077&&r.state==FPGA_SIM_DONE&&r.result);
    put(bytes+3+64,20000);put(bytes+3+52,500);
    assert(NativePset_Decode(bytes,99,&p));start(&r,&p);
    for(i=1;i<10000&&r.state==FPGA_SIM_RUNNING;i++)FpgaProgram_Tick(&r,i,1);
    assert(r.state==FPGA_SIM_FAULT&&r.fault_code==0x7006&&!r.result);
    /* 非法字段显式拒绝，失败保持调用方原工艺。 */
    frame(bytes);assert(NativePset_Decode(bytes,99,&p));old=p;
    put(bytes+3+64,30001);assert(!NativePset_Decode(bytes,99,&p)&&!memcmp(&old,&p,sizeof(p)));
    frame(bytes);put(bytes+3+8,100);assert(NativePset_Decode(bytes,99,&p)&&p.steps[0].decel_time_ms==100);
    put(bytes+3+8,60001);assert(!NativePset_Decode(bytes,99,&p));
    frame(bytes);bytes[3+22]=3;assert(!NativePset_Decode(bytes,99,&p));
    frame(bytes);bytes[3+23]=3;assert(!NativePset_Decode(bytes,99,&p));
    frame(bytes);put(bytes+3+84,1);assert(!NativePset_Decode(bytes,99,&p));
    frame(bytes);put(bytes+3+76,2);assert(!NativePset_Decode(bytes,99,&p));
    frame(bytes);put(bytes+3+80,2);assert(!NativePset_Decode(bytes,99,&p));
    frame(bytes);assert(!NativePset_Decode(bytes,98,&p));assert(!NativePset_Decode(bytes,100,&p));
    frame(bytes);bytes[2]=16;
    for(i=1;i<16;i++){memcpy(bytes+3+96*i,bytes+3,96);bytes[3+96*i+20]=(uint8_t)(i+1);}
    assert(NativePset_Decode(bytes,1539,&p)&&p.count==16);
    bytes[3+96*15+20]=15;assert(!NativePset_Decode(bytes,1539,&p));
    /* 两种已实现附加工步按HMI类型2/4映射，而非套用原生2/5编号。 */
    frame(bytes);memset(bytes+27,0,72);bytes[24]=2;
    put(bytes+27,1);put(bytes+31,6000);put(bytes+43,20000);put(bytes+51,1);put(bytes+55,1);
    assert(NativePset_Decode(bytes,99,&p)&&p.steps[0].kind==2&&p.steps[0].angle_cdeg==6000);
    put(bytes+51,0);put(bytes+55,0);assert(NativePset_Decode(bytes,99,&p)&&!p.steps[0].angle_reset&&!p.steps[0].torque_reset);
    put(bytes+51,2);assert(!NativePset_Decode(bytes,99,&p));
    put(bytes+51,0);put(bytes+55,2);assert(!NativePset_Decode(bytes,99,&p));
    frame(bytes);memset(bytes+27,0,72);bytes[24]=4;bytes[25]=2;
    put(bytes+27,20000);put(bytes+35,500);
    assert(NativePset_Decode(bytes,99,&p)&&p.steps[0].kind==5&&p.steps[0].direction==1);
    test_step_reset();
    test_step_entry_limit();
    return 0;
}
