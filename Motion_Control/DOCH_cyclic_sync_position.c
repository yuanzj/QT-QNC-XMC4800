/* 兼容C15通信层函数名；业务适配和模型在独立目录。 */
#include "DOCH_cyclic_sync_position.h"
#include "../Simulation/ethercat_adapter.h"
void SimulatedSlave_Tick(void) { Simulation_Tick(); }
void Pset_OnBufferReceived(uint16_t n) { Simulation_Receive(n); }
uint8_t Pset_IsRunning(void) { return Simulation_IsRunning(); }
uint32_t Pset_Crc32_Calc(const uint8_t *p, uint16_t n) { return Simulation_Crc32(p, n); }
