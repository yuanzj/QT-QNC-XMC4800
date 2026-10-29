# 客户 XMC4800 工程与最小 FPGA 模拟层

本仓库以客户交付的 `DOCH_ECAT_XMC48_Servo_Probe_20261018` 工程为原始版本，增加独立逻辑模拟层及当前 UIO 的通信适配，用于三板串联测试的首个通信示例。保留原许可证。

## 客户如何查看改动

- `customer-original-20261018`：客户原文件逐字节保存的原始标签。
- `FpgaSim/`：独立模拟模型，不包含 EtherCAT、SPI、寄存器或电机调用。
- `Simulation/`：PSET 参数校验、启停及对象字典反馈接入。
- `main.c`：取消原 ISR 无条件位置回显，避免覆盖模拟反馈。
- `SSC/`：单独从 C15 移植的通信适配；来源及摘要见 `Simulation/c15-reference.json`。
- `tools/`：构建、保留扇区空洞的刷写、真实 UIO 测试入口。

```shell
git log --oneline --reverse
git diff customer-original-20261018 HEAD -- FpgaSim Simulation main.c
git diff customer-original-20261018 HEAD -- SSC
```

恢复完整客户原版时使用原始标签。仅移除模拟模块不能恢复原对象字典和 PDO 布局。

## 首例：单工步等待 1 秒

UIO HTTP 测试入口 → 真实 EtherCAT SDO 下载 → 4800 接收参数 → FPGA 逻辑模拟计时 → PDO 反馈运行/成功 → UIO 确认结束。

PSET 为 16 B，编号 7、专家模式、1 个等待工步：

```text
07 02 01 04 0D 00 00 E8 03 00 00 D0 07 00 00 02
```

等待 1000 ms、上限 2000 ms、失败停止；CRC32/ISO-HDLC 为 `8f908a63`。运行时 `pset_echo=0x0701`，成功结束时 `pset_echo=0x0700`、`step_result=1`。

本例只接受时间型单等待，1～5000 ms；其他长度、工步或不支持的参数会标记参数错误。未实现完整拧紧、物理扳机或 SPI 帧模拟。当前逻辑接口是后续逐步扩展的接入点，不能当作客户实际 FPGA/SPI 接口定义。

## 为什么还修改 SSC

客户原版是 RxPDO 44 B、TxPDO 40 B，字段含义与当前 UIO 不同。为与现有 UIO 固件通信，单独复用 C15 已有的 RxPDO 12 B / TxPDO 40 B 及 SDO `0x2030/0x2031/0x2039/0x203A` 适配；没有把这项改动隐藏在模拟模型内。原 `0x2200/0x2201` 参数索引与业务状态冲突，适配后的参数为 `0x2210/0x2211`，具体变化可直接比较 SSC 提交。

SDO 最后接收长度和 CRC 不因模拟复位而伪造；运行中拒绝替换参数。模型支持停止、复位及 OP/控制器联锁，但本轮实板只验证正常等待路径，其余路径待补验。

## 构建与刷写

需要 Python 3.12、ARM GCC 14.2.1、J-Link。工具路径按本机安装位置替换。源码、SDK 和 SSC 文件已在本仓库，无需额外的 C12 压缩包。

```shell
python -X utf8 tools/build.py --gcc "<ARM-GCC>/bin/arm-none-eabi-gcc.exe" --output build/run01
python -X utf8 tools/flash.py --build build/run01 --jlink "<J-Link>/JLink.exe" --serial <探针序列号> --evidence evidence/preview01
# 核对预览后，使用另一个新的证据目录并增加 --confirm。
python -X utf8 tools/flash.py --build build/run01 --jlink "<J-Link>/JLink.exe" --serial <探针序列号> --evidence evidence/flash01 --confirm
python -X utf8 tools/test_wait.py --url "http://<UIO地址>:8080" --evidence evidence/business01 --repeat 3
python -X utf8 -m unittest discover -s tests -p "test_*.py" -v
```

构建、刷写和证据目录均不能覆盖。刷写只选择指定 XMC 探针，先完整备份 2 MiB，再合并受影响应用扇区的原有空洞；SII 区不写入，完整读回一致后才恢复 CPU。失败时保留暂停状态及日志，先检查失败阶段。

## DAVE 与调试

保留客户 `.project`，修正 `.cproject` 的工作区/头文件路径，并将 `tests/tools/build/evidence` 排除出 DAVE 编译。使用独立 DAVE 工作区导入，避免与同名客户原项目冲突。

已在 DAVE 4.5.0 内完成 Release/Debug 编译，并用 DAVE Debug 固件实板验证硬件断点、F6 单步、调用栈和变量读取。另用带空格的新路径、全新工作区、不携带构建缓存重新导入编译，HEX 一致。操作步骤与证据摘要见 [DAVE客户导入与断点调试说明](docs/DAVE客户导入与断点调试说明_20261030.md)。DAVE 自动代码生成尚未验证。

`Debug/Release` 是 IDE 自动生成的缓存，不再跟踪；客户原始标签仍完整保留原交付文件。命令行构建使用 `tools/source-list.json` 固定清单，避免被 IDE 重写缓存影响。若增加编译单元，DAVE会自动发现，命令行入口还需同步更新该清单。

调试必须使用板上同一份固件的 ELF。暂停 CPU 会影响 EtherCAT 周期；IDE 终止后也可能停在复位入口，须按说明恢复 CPU 和 UIO 从站，再进行业务测试。

## 验证边界

见 `docs/通信示例执行记录_20261030.md`。本例对应串联方案的基础通信及受控参数/反馈子项，按逻辑 FPGA 替代和直接模拟结果标记范围；没有验证物理 SPI、真实算法、实际扭矩和电机安全功能。本例由 UIO 诊断入口发起，没有完成 HMI 发起的 G1 首颗验收，也没有将整个 TC-HIL 场景组改签通过。

仓库不含现场数据库、私钥、口令、原始通信日志或刷写备份；这些运行证据保存在本机忽略目录。
