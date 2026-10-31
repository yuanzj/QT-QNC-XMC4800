/* Explicit negative PDO mapping profile for TC-HIL-MAP-05.
 * Scenario 7 advertises/writes 36-byte TxPDO; default remains 40 bytes.
 * Test-only logical boundary, not a production protocol revision. */
#ifndef SIMULATION_TEST_MAPPING_H
#define SIMULATION_TEST_MAPPING_H
#ifndef FPGA_SIM_SCENARIO
#define FPGA_SIM_SCENARIO 0
#endif
#if FPGA_SIM_SCENARIO == 7
#define SIMULATION_TX_PDO_ENTRY_COUNT 12
#define SIMULATION_TX_PDO_BYTES 36
#else
#define SIMULATION_TX_PDO_ENTRY_COUNT 13
#define SIMULATION_TX_PDO_BYTES 40
#endif
#endif
