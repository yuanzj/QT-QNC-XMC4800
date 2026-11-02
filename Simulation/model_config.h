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
/* 显式保留旧40B/500rpm；新场景9默认使用INT64/44B/1000rpm。 */
#ifndef FPGA_SIM_INT64
#define FPGA_SIM_INT64 (FPGA_SIM_SCENARIO == 9)
#endif
#if FPGA_SIM_INT64 != 0 && FPGA_SIM_INT64 != 1
#error FPGA_SIM_INT64 must be 0 or 1
#endif
#if FPGA_SIM_INT64 && FPGA_SIM_SCENARIO != 9
#error INT64 feedback requires the independent scenario 9 model
#endif
#ifndef FPGA_MODEL_IDENTITY_VALID
#define FPGA_MODEL_IDENTITY_VALID 1
#endif
#if FPGA_MODEL_IDENTITY_VALID != 0 && FPGA_MODEL_IDENTITY_VALID != 1
#error FPGA_MODEL_IDENTITY_VALID must be 0 or 1
#endif
#if FPGA_SIM_INT64
#define FPGA_MODEL_SPEC_CODE 0 /* 未分配正式码，不能把历史模拟值1冒充正式型号。 */
#define FPGA_MODEL_MAX_RPM_MILLI 1000000UL
#else
#define FPGA_MODEL_SPEC_CODE 1 /* 保留旧镜像历史字节，不代表正式码表。 */
#define FPGA_MODEL_MAX_RPM_MILLI 500000UL
#endif
#endif
