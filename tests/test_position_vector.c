/* 场景5独立时刻/原始整数预期；断点、符号和联锁不依赖HMI测试代码。 */
#ifdef NDEBUG
#error Compile with assertions enabled
#endif
#if FPGA_SIM_SCENARIO != 5
#error Compile this test with FPGA_SIM_SCENARIO=5
#endif
#include <assert.h>
#include <string.h>
#include "../FpgaSim/fpga_program.h"

static FpgaProgram program(uint8_t count, uint8_t reverse)
{
    FpgaProgram p;
    memset(&p, 0, sizeof(p));
    p.pset_no = 107;
    p.count = count;
    p.steps[0].kind = 3;
    p.steps[0].direction = reverse;
    p.steps[0].angle_reset = 1;
    p.steps[0].failure_action = 2;
    p.steps[0].duration_ms = 1000;
    p.steps[0].timeout_ms = 2000;
    p.steps[0].torque_mnm = 11000;
    p.steps[0].angle_cdeg = 1200;
    p.steps[0].min_torque_mnm = 10000;
    p.steps[0].max_torque_mnm = 12000;
    p.steps[0].min_angle_cdeg = 1000;
    p.steps[0].max_angle_cdeg = 1400;
    p.steps[1] = p.steps[0];
    p.steps[1].direction = reverse ? 0 : 1;
    return p;
}

int main(void)
{
    FpgaProgramRun run;
    FpgaProgram p;
    uint8_t reverse;
    for (reverse = 0; reverse <= 1; ++reverse) {
        int32_t first = reverse ? -2147483000L : 2147483000L;
        p = program(1, reverse);
        FpgaProgram_Reset(&run);
        assert(FpgaProgram_Load(&run, &p) && FpgaProgram_Start(&run, 0, 1));
        FpgaProgram_Tick(&run, 0, 1); assert(run.position_inc == first && run.current_step == 1);
        FpgaProgram_Tick(&run, 299, 1); assert(run.position_inc == first && run.current_step == 1);
        FpgaProgram_Tick(&run, 300, 1); assert(run.position_inc == -first && run.current_step == 1);
        FpgaProgram_Tick(&run, 999, 1); assert(run.position_inc == -first && run.current_step == 1);
        FpgaProgram_Tick(&run, 1000, 1); assert(run.state == FPGA_SIM_DONE && run.result && run.position_inc == -first);
        p = program(2, reverse);
        FpgaProgram_Reset(&run); assert(FpgaProgram_Load(&run, &p) && FpgaProgram_Start(&run, 0, 1));
        FpgaProgram_Tick(&run, 0, 1); assert(run.position_inc == first);
        FpgaProgram_Tick(&run, 1000, 1); assert(run.current_step == 1 && run.pending_next && run.position_inc == first);
        FpgaProgram_Tick(&run, 1019, 1); assert(run.current_step == 1 && run.position_inc == first);
        FpgaProgram_Tick(&run, 1020, 1); assert(run.current_step == 2 && run.position_inc == -first);
        FpgaProgram_Tick(&run, 2020, 1); assert(run.state == FPGA_SIM_DONE && run.result);
    }
    p = program(2, 0); p.steps[1].kind = 4; p.steps[1].duration_ms = 100; p.steps[1].torque_mnm = 0; p.steps[1].angle_cdeg = 0;
    FpgaProgram_Reset(&run); assert(FpgaProgram_Load(&run, &p) && FpgaProgram_Start(&run, 0, 1));
    FpgaProgram_Tick(&run, 1000, 1); assert(run.position_inc == 2147483000L);
    FpgaProgram_Tick(&run, 1020, 1); assert(run.current_step == 2 && run.position_inc == 0);
    FpgaProgram_Tick(&run, 1120, 1); assert(run.state == FPGA_SIM_DONE && run.result);
    p = program(1, 0);
    FpgaProgram_Reset(&run); assert(FpgaProgram_Load(&run, &p) && FpgaProgram_Start(&run, 0, 1));
    FpgaProgram_Tick(&run, 300, 0); assert(run.state == FPGA_SIM_FAULT && run.position_inc == 0);
    FpgaProgram_Stop(&run); FpgaProgram_Tick(&run, 400, 1); assert(run.state == FPGA_SIM_STOPPED);
    return 0;
}
