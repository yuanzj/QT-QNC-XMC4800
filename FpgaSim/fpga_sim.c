/* 逻辑FPGA替代实现；本例不模拟SPI字节帧，也不实现实际拧紧算法。 */
#include "fpga_sim.h"

void FpgaSim_Reset(FpgaSim *sim)
{
    sim->state = FPGA_SIM_IDLE;
    sim->started_ms = 0;
    sim->duration_ms = 0;
    sim->result = 0;
}

uint8_t FpgaSim_LoadWait(FpgaSim *sim, uint16_t duration_ms)
{
    if (sim->state == FPGA_SIM_RUNNING || duration_ms == 0 || duration_ms > 5000) return 0;
    sim->duration_ms = duration_ms;
    sim->result = 0;
    sim->state = FPGA_SIM_READY;
    return 1;
}

uint8_t FpgaSim_Start(FpgaSim *sim, uint32_t now_ms, uint8_t permitted)
{
    if (!permitted || sim->duration_ms == 0 ||
        (sim->state != FPGA_SIM_READY && sim->state != FPGA_SIM_DONE &&
         sim->state != FPGA_SIM_STOPPED)) return 0;
    sim->started_ms = now_ms;
    sim->result = 0;
    sim->state = FPGA_SIM_RUNNING;
    return 1;
}

void FpgaSim_Stop(FpgaSim *sim)
{
    sim->result = 0;
    sim->state = FPGA_SIM_STOPPED;
}

void FpgaSim_Tick(FpgaSim *sim, uint32_t now_ms, uint8_t permitted)
{
    if (sim->state != FPGA_SIM_RUNNING) return;
    if (!permitted) {
        sim->state = FPGA_SIM_FAULT;
        sim->result = 0;
        return;
    }
    if ((uint32_t)(now_ms - sim->started_ms) >= sim->duration_ms) {
        sim->state = FPGA_SIM_DONE;
        sim->result = 1;
    }
}
