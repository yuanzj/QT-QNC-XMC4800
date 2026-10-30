# 逻辑FPGA模型与实板资格验证 v0.2

本版本在客户原工程及v0.1.1单等待示例上扩展。客户原文件仍保存在`customer-original-20261018`标签，既有`fpga-sim-wait-v0.1.1`标签不改写。所有变化均可通过Git查看。

## 1. 模块与能力边界

| 文件 | 职责 |
|---|---|
| `FpgaSim/fpga_program.c/.h` | 纯C确定性反馈、1ms逻辑时序、启停、联锁、失败继续/停止、最多16工步；不含SPI、寄存器或电机调用 |
| `Simulation/native_pset.c/.h` | 解码本轮原生专家PSET字节、长度及必要范围；不负责HMI翻译或完整生产参数准入 |
| `Simulation/ethercat_adapter.c` | 接收真实SDO缓冲区、消费控制命令、向实际对象字典发布反馈 |
| `tools/test_native_model.py` | 诊断任务、长度/CRC、独立原始量预期、连续TCP过程流和工步事件核对 |

旧`fpga_sim.c/.h`及其等待测试保留。当前运行入口为`Simulation_Tick → FpgaProgram_Tick`，旧`FpgaSim_Tick`不再是本版本运行断点。

仅接受专家模式`create_mode=2`、PSET号1～254、1～16工步。原生类型与HMI类型是两套枚举：

| 原生编号 | 长度 | 模型行为 |
|---|---:|---|
| 1 认帽 | 22B | 所用目标的确定性斜坡 |
| 2 快速下旋 | 36B | 确定性斜坡，读取本轮超时、延迟和失败动作 |
| 3 拧紧 | 61B | 扭矩/角度斜坡及模型窗口OK/NOK |
| 4 WAIT | 13B | 时间等待1～5000ms；不是HMI卸荷4 |
| 5 卸荷 | 26B | 负角度斜坡；不是HMI拧松5 |
| 6 OUTPUT | 5B | 20ms逻辑完成，不操作实际DO |

运动类统一1000ms线性试验时序，可加模型延迟。速度、加速度、实际扭矩法/转角法/组合策略、斜率、标定K/B、传感器、SPI及扳机电气时序未建模。收到字段字节不等于按真实算法执行。方向仅支持列明的正/反转，交替方向和失败跳转不支持。

参考模拟规格为8388608 inc/圈、减速比30、扭矩换算满量程30000mN·m。11N·m连续额定值不是本轮原始扭矩换算基准。这是模型约定，不能当实际工具已校准。

```
torque_raw = torque_mNm × 1000 ÷ 30000
position_inc = angle_cdeg × 8388608 × 30 ÷ 36000
```

64位中间量、整数除法量化；越界拒绝或报模型故障，不静默饱和/回绕。11N·m对应366，±12°对应±8388608 inc。

## 2. 接收与时序保护

原生`0x220D`为最近完成工步的0/1结果。步间保留20ms完成反馈，进入下一步保留上一结果，供现有UIO边沿收口。任一步NOK后即使继续且后续成功，整链仍为NOK。

STOP优先于同拍完成；RESET清除可启动任务；联锁失效先于成功判定。不合法新SDO撤销可启动标记，不能启动旧程序。运行中SDO替换由原接收层拒绝。长度/CRC摘要不因模拟复位而伪造。

宿主断言覆盖上述规则；实板主要覆盖正常和四类异常反馈。尚未完成HMI正常停止/复位链、物理联锁及真实电机安全测试，不能用模型断言代签。

## 3. 构建与复现

```shell
python -X utf8 tools/build.py --gcc "<ARM-GCC>/bin/arm-none-eabi-gcc.exe" --output build/model-normal --scenario 0
python -X utf8 tools/flash.py --build build/model-normal --jlink "<J-Link>/JLink.exe" --serial <XMC探针号> --evidence evidence/model-normal-flash --confirm
python -X utf8 tools/test_native_model.py --url "http://<UIO地址>:8080" --evidence evidence/model-normal-run --which all --repeat 3 --frames "<原样TCP采集的frames.ndjson>"
```

场景0正常、1扭矩超上限、2角度超上限、3超时、4未知故障。异常固件仅运行`--which snug --scenario <编号>`。`0x7001`是显式测试未知码，不是生产故障码。其他NOK场景仅提供失败结果，不代表精确生产失败归因已经验证。

多工步需提供连续TCP采集文件，HTTP轮询会漏看短工步。工具通过UIO诊断入口发起，不能替代HMI G1。长度/CRC回读不是完整SDO字节回读。输出不覆盖；固定XMC探针，备份2MiB、跳过SII、保留扇区空洞，完整回读一致后才恢复CPU。异常测试结束应恢复场景0复测。

## 4. 已执行资格运行

GCC14.2.1：单拧紧、反转、六工步、16工步、等待各3次共15次；扭矩NOK、角度NOK、超时、未知故障各3次，恢复正常再3次，总计30次。各场景WKC错误和RPMsg丢弃增量均为0。30次循环ID、开始/工步/结束事件与实际HMI数据库逐ID核对一致。汇总扭矩/角度按既有业务口径取最后一个拧紧步，不取卸荷后的整链末值。

保留早期失败：无效新参数可能重跑旧任务、切步过早清除结果、误用11N·m换算、HTTP漏看短工步。前三项修正模型并回归，最后一项改用连续流取证。旧轮次不补签物理量一致。宿主C测试五种场景、接收适配器及旧等待模型通过，显式`-UNDEBUG`；Python刷写工具3项测试通过。固定构建清单为85个单元。

## 5. v0.2资格验证时的DAVE版本及断点

本节保留该次实测的ELF和断点证据。后续增加可选位置场景5后，普通HEX相同，源码匹配ELF已更新；当前板上镜像及恢复记录见[位置边界验证](原始位置边界向量与恢复验证_v0.1_20261030.md)，不要将本节旧ELF与新源码混用。

DAVE4.5.0自带GCC4.9.3，使用新工作区重新导入，Debug/Release均编译完成。Debug HEX：

`44311e5a6ba00a5e15af18f2e7b37643179479e003bdf04afaf6d02bdbbb2443`

Debug ELF：`6ebc21ce16f714eeb0fd8aa5318e0615dcd18419b2c26bf6b6c966e58c8356e6`。

已刷入同一Debug镜像、完整回读并保留SII。使用DAVE自带GDB7.10.1实际命中`Simulation_Tick`第67行硬件断点，单步到第70行，读取`simulator`，调用栈追溯到实际EtherCAT中断及main。本次是GDB批处理补验，不将旧版GUI证据当新模型GUI复验。退出调试后恢复CPU和OP，15次正常模型运行均通过，WKC错误和RPMsg丢弃增量均为0。

```shell
python -X utf8 tools/configure_dave_debug.py --dave "<DAVE目录>" --jlink-server "<J-Link>/JLinkGDBServerCL.exe" --serial <XMC探针号> --output XMC4800-MODEL-Attach.local.launch
```

模板已改为`hbreak Simulation_Tick`。旧本机launch不覆盖，需生成新配置。IDE关闭自动下载，符号必须与板上镜像对应。导入及恢复操作见[DAVE说明](DAVE客户导入与断点调试说明_20261030.md)。DAVE自动代码生成仍未验证。

## 6. 剩余真实链路验收

普通HMI IO配置/PSET下载返回10015，工具身份无有效值，阻塞正常G1。UIO保持不改，不能通过硬改HMI同步、补假SN或伪就绪绕开。真实FPGA/SPI、生产算法、实际工具/IO/STO、HMI受控业务及长测另行补验。
