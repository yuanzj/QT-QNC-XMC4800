/* EtherCAT对象字典到逻辑FPGA模拟模块的接入点，非物理SPI协议。 */
#ifndef SIMULATION_ETHERCAT_ADAPTER_H
#define SIMULATION_ETHERCAT_ADAPTER_H
#include <stdint.h>
void Simulation_Tick(void);
void Simulation_Receive(uint16_t length);
uint8_t Simulation_IsRunning(void);
uint32_t Simulation_Crc32(const uint8_t *bytes, uint16_t length);
#endif
