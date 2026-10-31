/* 场景9为参数驱动+独立合成接头；0~8保留为明确的协议测试向量。 */
#ifndef SIMULATION_MODEL_CONFIG_H
#define SIMULATION_MODEL_CONFIG_H
#ifndef FPGA_SIM_SCENARIO
#define FPGA_SIM_SCENARIO 9
#endif
#ifndef FPGA_MODEL_PROFILE
#define FPGA_MODEL_PROFILE 1
#endif
#if FPGA_SIM_SCENARIO < 0 || FPGA_SIM_SCENARIO > 9
#error Unsupported FPGA_SIM_SCENARIO
#endif
#if FPGA_MODEL_PROFILE < 1 || FPGA_MODEL_PROFILE > 4
#error Unsupported independent joint profile
#endif
#endif
