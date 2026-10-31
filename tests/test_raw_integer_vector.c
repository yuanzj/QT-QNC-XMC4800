/* 原始量极值模型的独立时刻预期；强制断言及整数未定义行为检查。 */
#ifdef NDEBUG
#error Compile with -UNDEBUG
#endif
#if FPGA_SIM_SCENARIO != 8
#error Compile this test with FPGA_SIM_SCENARIO=8
#endif
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "../FpgaSim/fpga_program.h"
int main(void)
{
    const int16_t tq[10] = {-32768, -1, 0, 1, 32767, 1000, 0, 123, 2000, 0};
    const int32_t position[10] = {(-2147483647 - 1), -1, 0, 1, 2147483647, 8388608, 0, -8388608, 4194304, 0};
    FpgaProgram p; FpgaProgramRun run; unsigned i;
    memset(&p, 0, sizeof(p)); p.pset_no=119; p.count=1;
    p.steps[0].kind=3; p.steps[0].angle_reset=1; p.steps[0].failure_action=2;
    p.steps[0].duration_ms=1000; p.steps[0].timeout_ms=2000;
    p.steps[0].torque_mnm=11000; p.steps[0].min_torque_mnm=10000; p.steps[0].max_torque_mnm=12000;
    p.steps[0].angle_cdeg=1200; p.steps[0].min_angle_cdeg=1000; p.steps[0].max_angle_cdeg=1400;
    FpgaProgram_Reset(&run); assert(FpgaProgram_Load(&run,&p)); assert(FpgaProgram_Start(&run,0,1));
    for(i=0;i<1000;++i) {
        FpgaProgram_Tick(&run,i,1);
        assert(run.state==FPGA_SIM_RUNNING && run.current_step==1);
        assert(run.torque_raw==tq[i/100] && run.position_inc==position[i/100] && run.velocity_inc_s==position[i/100]);
    }
    FpgaProgram_Tick(&run,1000,1); assert(run.state==FPGA_SIM_DONE && run.result==1);
    assert(run.torque_raw==0 && run.position_inc==0 && run.velocity_inc_s==0);
    assert(FpgaProgram_Start(&run,2000,1)); FpgaProgram_Tick(&run,2001,0);
    assert(run.state==FPGA_SIM_FAULT && run.fault_code==3 && run.position_inc==0);
    FpgaProgram_Stop(&run); FpgaProgram_Tick(&run,3000,1); assert(run.state==FPGA_SIM_STOPPED && run.velocity_inc_s==0);
    return 0;
}
