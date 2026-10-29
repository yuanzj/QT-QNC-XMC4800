/* 宿主状态机测试：边界、提前完成、停止优先、联锁及32位时钟回绕。 */
#include <assert.h>
#include "../FpgaSim/fpga_sim.h"
int main(void)
{
    FpgaSim sim;
    FpgaSim_Reset(&sim);
    assert(!FpgaSim_Start(&sim, 0, 1));
    assert(!FpgaSim_LoadWait(&sim, 0));
    assert(!FpgaSim_LoadWait(&sim, 5001));
    assert(FpgaSim_LoadWait(&sim, 1000));
    assert(!FpgaSim_Start(&sim, 100, 0));
    assert(FpgaSim_Start(&sim, 100, 1));
    assert(!FpgaSim_LoadWait(&sim, 2));
    assert(sim.duration_ms == 1000);
    FpgaSim_Tick(&sim, 1099, 1);
    assert(sim.state == FPGA_SIM_RUNNING && !sim.result);
    FpgaSim_Tick(&sim, 1100, 0);
    assert(sim.state == FPGA_SIM_FAULT && !sim.result);
    FpgaSim_Reset(&sim);
    assert(FpgaSim_LoadWait(&sim, 1000));
    assert(FpgaSim_Start(&sim, 0xFFFFFF00u, 1));
    FpgaSim_Tick(&sim, 0x2E7u, 1);
    assert(sim.state == FPGA_SIM_RUNNING);
    FpgaSim_Tick(&sim, 0x2E8u, 1);
    assert(sim.state == FPGA_SIM_DONE && sim.result);
    assert(FpgaSim_Start(&sim, 0, 1));
    FpgaSim_Stop(&sim);
    FpgaSim_Tick(&sim, 1000, 1);
    assert(sim.state == FPGA_SIM_STOPPED && !sim.result);
    return 0;
}
