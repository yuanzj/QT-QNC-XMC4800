/* Explicit negative PDO mapping profile for TC-HIL-MAP-05.
 * Scenario 7: 36B negative; legacy: 40B; INT64 scenario 9: 44B.
 * Test-only logical boundary, not a production protocol revision. */
#ifndef SIMULATION_TEST_MAPPING_H
#define SIMULATION_TEST_MAPPING_H
#include "model_config.h"
#if FPGA_SIM_SCENARIO == 7
#define SIMULATION_TX_PDO_ENTRY_COUNT 12
#define SIMULATION_TX_PDO_BYTES 36
#elif FPGA_SIM_INT64
#define SIMULATION_TX_PDO_ENTRY_COUNT 13
#define SIMULATION_TX_PDO_BYTES 44
#else
#define SIMULATION_TX_PDO_ENTRY_COUNT 13
#define SIMULATION_TX_PDO_BYTES 40
#endif
#if FPGA_SIM_INT64
#define SIMULATION_VELOCITY_MAP_ENTRY 0x22120040
#else
#define SIMULATION_VELOCITY_MAP_ENTRY 0x606C0020
#endif
#endif
