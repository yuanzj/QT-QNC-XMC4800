/* 独立输入/预期：实际字段编码、原始量换算、时钟回绕、NOK继续/停止和参数拒绝。 */
#ifdef NDEBUG
#error Compile tests with -UNDEBUG so assertions execute
#endif
#include <assert.h>
#include <limits.h>
#include <string.h>
#include "../Simulation/native_pset.h"

static void put32(uint8_t *p, uint32_t n)
{ p[0]=(uint8_t)n; p[1]=(uint8_t)(n>>8); p[2]=(uint8_t)(n>>16); p[3]=(uint8_t)(n>>24); }

static FpgaProgram wait_program(void)
{
    const uint8_t input[16] = {7,2,1,4,13,0,0,0xE8,3,0,0,0xD0,7,0,0,2};
    FpgaProgram program;
    assert(NativePset_Decode(input,sizeof(input),&program));
    assert(program.pset_no==7 && program.count==1 && program.steps[0].duration_ms==1000);
    return program;
}

static FpgaProgram snug_program(void)
{
    uint8_t input[64]={1,2,1,3,61,0};
    uint8_t *s=input+3;
    FpgaProgram program, unchanged;
    uint16_t i;
    s[3]=1;put32(s+4,10000);put32(s+8,12000);put32(s+12,8000);
    put32(s+24,1000);put32(s+28,2000);put32(s+36,1500);
    s[40]=0;put32(s+41,100000);s[49]=1;s[50]=1;s[51]=0x10;s[52]=0x27;s[55]=2;s[56]=2;
    assert(NativePset_Decode(input,sizeof(input),&program));
    assert(program.steps[0].torque_mnm==10000 && program.steps[0].angle_cdeg==1500);
    unchanged=program;
    for(i=0;i<sizeof(input);++i) {
        assert(!NativePset_Decode(input,i,&unchanged));
        assert(memcmp(&program,&unchanged,sizeof(program))==0);
    }
    input[2]=17;assert(!NativePset_Decode(input,sizeof(input),&unchanged));input[2]=1;
    put32(s+12,13000);assert(!NativePset_Decode(input,sizeof(input),&unchanged));put32(s+12,8000);
    s[0]=7;assert(!NativePset_Decode(input,sizeof(input),&unchanged));
    return program;
}

int main(void)
{
    FpgaProgramRun run;
    FpgaProgram program=wait_program();
    FpgaProgram snug=snug_program();
    int16_t torque;
    int32_t position;
    assert(FpgaProgram_Convert(30000,1200,&torque,&position));
    assert(torque==1000 && position==8388608);
    assert(FpgaProgram_Convert(-30000,-1200,&torque,&position));
    assert(torque==-1000 && position==-8388608);
    assert(!FpgaProgram_Convert(0,307200,&torque,&position));
    assert(FpgaProgram_Convert(0,-307200,&torque,&position) && position==INT32_MIN);
    FpgaProgram_Reset(&run);
    assert(!FpgaProgram_Start(&run,0,1));
    assert(FpgaProgram_Load(&run,&program));
    assert(!FpgaProgram_Start(&run,0,0));
    assert(FpgaProgram_Start(&run,0xFFFFFF00u,1));
    assert(!FpgaProgram_Load(&run,&snug) && run.program.pset_no==7);
    FpgaProgram_Tick(&run,0x2E7u,1);assert(run.state==FPGA_SIM_RUNNING);
    FpgaProgram_Tick(&run,0x2E8u,0);assert(run.state==FPGA_SIM_FAULT && !run.result);
    FpgaProgram_Reset(&run);assert(FpgaProgram_Load(&run,&program));assert(FpgaProgram_Start(&run,0,1));
    FpgaProgram_Stop(&run);FpgaProgram_Tick(&run,1000,1);assert(run.state==FPGA_SIM_STOPPED && !run.result);
    assert(FpgaProgram_Start(&run,2000,1));FpgaProgram_Tick(&run,3000,1);
    assert(run.state==FPGA_SIM_DONE && run.result);

    program.count=2;program.steps[0].duration_ms=100;program.steps[1]=program.steps[0];
    FpgaProgram_Reset(&run);assert(FpgaProgram_Load(&run,&program));assert(FpgaProgram_Start(&run,0,1));
    FpgaProgram_Tick(&run,100,1);assert(run.current_step==1 && run.pending_next && run.result);
    FpgaProgram_Tick(&run,119,1);assert(run.current_step==1);
    FpgaProgram_Tick(&run,120,1);assert(run.current_step==2 && run.result);
    FpgaProgram_Tick(&run,121,1);assert(run.current_step==2 && run.result);
    FpgaProgram_Tick(&run,220,1);assert(run.state==FPGA_SIM_DONE && run.result);

    FpgaProgram_Reset(&run);assert(FpgaProgram_Load(&run,&snug));assert(FpgaProgram_Start(&run,0,1));
    FpgaProgram_Tick(&run,1000,1);
#if FPGA_SIM_SCENARIO == 4
    assert(run.state==FPGA_SIM_FAULT && run.fault_code==0x7001 && !run.result);
#elif FPGA_SIM_SCENARIO == 1 || FPGA_SIM_SCENARIO == 2
    assert(run.state==FPGA_SIM_DONE && !run.result);
#elif FPGA_SIM_SCENARIO == 3
    assert(run.state==FPGA_SIM_RUNNING);
    FpgaProgram_Tick(&run,10000,1);assert(run.state==FPGA_SIM_DONE && !run.result);
#else
    assert(run.state==FPGA_SIM_DONE && run.result && run.torque_raw==333 && run.position_inc==10485760);
    snug.count=2;snug.steps[0].min_torque_mnm=11000;snug.steps[0].failure_action=1;
    snug.steps[1]=program.steps[0];
    FpgaProgram_Reset(&run);assert(FpgaProgram_Load(&run,&snug));assert(FpgaProgram_Start(&run,0,1));
    FpgaProgram_Tick(&run,1000,1);assert(run.pending_next && !run.result);
    FpgaProgram_Tick(&run,1020,1);assert(run.current_step==2);
    FpgaProgram_Tick(&run,1120,1);assert(run.state==FPGA_SIM_DONE && !run.result);
    snug.steps[0].failure_action=2;
    FpgaProgram_Reset(&run);assert(FpgaProgram_Load(&run,&snug));assert(FpgaProgram_Start(&run,0,1));
    FpgaProgram_Tick(&run,1000,1);assert(run.state==FPGA_SIM_DONE && !run.result);
#endif
    return 0;
}
