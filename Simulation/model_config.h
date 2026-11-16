/* 场景9为参数驱动+独立合成接头；0~8保留为明确的协议测试向量。 */
#ifndef SIMULATION_MODEL_CONFIG_H
#define SIMULATION_MODEL_CONFIG_H
/* C20-compatible EtherCAT/SDO sidecar, independent joint engine unchanged. */
#ifndef FPGA_C20_PROFILE
#define FPGA_C20_PROFILE 0
#endif
#if FPGA_C20_PROFILE != 0 && FPGA_C20_PROFILE != 1
#error FPGA_C20_PROFILE must be 0 or 1
#endif
#define XMC_QIAOTIAN_20261109 FPGA_C20_PROFILE
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
/* MAP-05隔离负例：只省去TxPDO末尾8字节填充，真实字段和型号保持场景9原布局。 */
#ifndef FPGA_TEST_TRUNCATE_TXPDO_TAIL
#define FPGA_TEST_TRUNCATE_TXPDO_TAIL 0
#endif
#if FPGA_TEST_TRUNCATE_TXPDO_TAIL != 0 && FPGA_TEST_TRUNCATE_TXPDO_TAIL != 1
#error FPGA_TEST_TRUNCATE_TXPDO_TAIL must be 0 or 1
#endif
#if FPGA_TEST_TRUNCATE_TXPDO_TAIL && (!FPGA_SIM_INT64 || FPGA_SIM_SCENARIO != 9)
#error Negative PDO tail requires independent scenario 9 INT64
#endif
/* MAP-04显式协议故障向量，仅改变发布的位置，不改变接头/控制器内部反馈及判定。 */
#ifndef FPGA_TEST_POSITION_VECTOR
#define FPGA_TEST_POSITION_VECTOR 0
#endif
#if FPGA_TEST_POSITION_VECTOR < 0 || FPGA_TEST_POSITION_VECTOR > 3
#error Unsupported position test vector
#endif
#if FPGA_TEST_POSITION_VECTOR && (!FPGA_SIM_INT64 || FPGA_SIM_SCENARIO != 9 || FPGA_TEST_TRUNCATE_TXPDO_TAIL)
#error Position test vector requires independent scenario 9 INT64 and normal PDO length
#endif
#ifndef FPGA_MODEL_IDENTITY_VALID
#define FPGA_MODEL_IDENTITY_VALID 1
#endif
#if FPGA_MODEL_IDENTITY_VALID != 0 && FPGA_MODEL_IDENTITY_VALID != 1
#error FPGA_MODEL_IDENTITY_VALID must be 0 or 1
#endif
/* 默认关闭的完整SDO工艺提交取证；只写RAM计数，不进入协议或接头模型。 */
#ifndef FPGA_TEST_SDO_COMMIT_TRACE
#define FPGA_TEST_SDO_COMMIT_TRACE 0
#endif
#if FPGA_TEST_SDO_COMMIT_TRACE != 0 && FPGA_TEST_SDO_COMMIT_TRACE != 1
#error FPGA_TEST_SDO_COMMIT_TRACE must be 0 or 1
#endif
#if FPGA_TEST_SDO_COMMIT_TRACE && (FPGA_SIM_SCENARIO != 9 || !FPGA_SIM_INT64 || !FPGA_MODEL_IDENTITY_VALID || FPGA_TEST_POSITION_VECTOR || FPGA_TEST_TRUNCATE_TXPDO_TAIL)
#error SDO commit trace requires the normal independent scenario 9 INT64 simulation profile
#endif
#if FPGA_C20_PROFILE && (FPGA_SIM_SCENARIO != 9 || !FPGA_SIM_INT64 || FPGA_TEST_TRUNCATE_TXPDO_TAIL || FPGA_TEST_POSITION_VECTOR)
#error C20 profile requires independent joint, INT64 and normal physical mapping
#endif
#if FPGA_SIM_INT64
#define FPGA_MODEL_SPEC_CODE 0 /* 未分配正式码，不能把历史模拟值1冒充正式型号。 */
#define FPGA_MODEL_MAX_RPM_MILLI 1000000UL
#else
#define FPGA_MODEL_SPEC_CODE 1 /* 保留旧镜像历史字节，不代表正式码表。 */
#define FPGA_MODEL_MAX_RPM_MILLI 500000UL
#endif
#endif
