# 工具型号只读快照与UIO对接

版本v0.5，2026-11-02。新增功能参考接口，先ARM编译与宿主验证，不刷板，不修改UIO代码。与已有INT64/1000rpm一起交付，Windows历史记录与旧参考数据保留。客户真实电子铭牌/码表仍需真实实现，本项目未替客户分配正式型号代码。

## 只读对象

新增厂商SDO `0x2214:00`：OCTET_STRING、192bit/24B、只读、不加入PDO。只接受子索引0、非CompleteAccess、24B读取；不改变0x2000的12个子索引或map4的13项44B布局。

| 偏移 | 长度 | 含义 |
|---|---:|---|
| 0 | 16 | 型号名ASCII，大写字母/数字/短横线；短串补0，最长16字符 |
| 16 | 4 | 正式码表版本UINT32小端，无效0 |
| 20 | 1 | 型号代码UINT8，与2000:02一致；无效0 |
| 21 | 1 | 有效位bit0名称、bit1代码、bit2码表；其余0 |
| 22 | 1 | 来源0未知、1真实铭牌直读、2正式码表、3显式模拟 |
| 23 | 1 | 保留0 |

新INT64模式默认SIM-QNC30、mask=1、source=3、代码/码表为0。名称明确标记模拟，不代表实际型号；2000:02由历史占位1改为0，避免被当成正式型号分配。`--model unknown`得到全零24B。实际客户应以真实工具铭牌或正式码表替换，不复制模拟名称/正式代码占位，不根据SN、量程或工艺参数反推型号。原工具SN本轮不改。

legacy模式不增加2214对象，2000:02保留历史字节1，兼容原40B/500rpm；该历史占位不能视为正式码表。本次只新增只读规格信息，不改独立接头、传感量、控制目标或保护，不预设拧紧成功。

## UIO实现要求

UIO读2000:01工具SN→读2214快照→再次读SN，必须一致；并核对2214代码与2000:02。读取失败或来源未知，型号字段全0上报；不能使用另一把工具或前次连接的缓存。真实客户实现若动态更新铭牌须保证这份24B快照一致。

HMI链路新增VER6的4009/48B，能力bit25（24已用于故障恢复）：boot_id U32@0、tool_sn CHAR16@4、model CHAR16@20、码表版本U32@36、代码U8@40、valid_mask U8@41、source U8@42、reserved0@43、sample_seq U32@44。名字/SN可占满16B。收到成功握手应答后1s内首报，变化立即报、每5s全量；新快照序号从1递增。C009/4B：0成功、30004字段/身份拒绝、1业务/存储失败；不占event_seq或循环补传水位。

型号必须绑定当前握手SN和boot_id，换枪先握手；HMI校验能力/身份/单调序号，重复幂等，断线/重连/换枪清当前状态，15s无新快照过期。HMI使用既有型号格并标“模拟”，工艺仍绑定SN、旧记录不重写。完整协议以同批v6增补§7为准，固件不能自行改握手长度或占PDO保留区。

## 构建与软件验证

```shell
python3 tools/build.py --gcc "<GCC>/bin/arm-none-eabi-gcc" --output build/model-hard --velocity int64 --joint hard --model simulation
python3 tools/build.py --gcc "<GCC>/bin/arm-none-eabi-gcc" --output build/model-unknown --velocity int64 --joint hard --model unknown
python3 tools/build.py --gcc "<GCC>/bin/arm-none-eabi-gcc" --output build/model-legacy --velocity legacy --joint hard
python3 tools/test_model_profiles.py --cc clang --output evidence/model-host
```

默认DAVE导入宏FPGA_SIM_SCENARIO=9、FPGA_SIM_INT64=1、FPGA_MODEL_IDENTITY_VALID=1；未知使用最后一项0。原固定88编译单元不增加，只加头文件/SDO回调。manifest登记型号来源、型号对象和是否分配正式代码。测试提取实际SDO回调/描述符，校验模拟/未知24B、小端字节、长度/子索引/访问拒绝及写缓冲边界；旧23个模型运行、4个PDO配置和速度SDO继续回归。刷写保全算法测试用临时数据，不碰探针。

本轮未刷板、未改UIO、未做SDO→UIO→本地HMI实板联测。新增代码也未重做Windows/DAVE资格测试，旧Windows文档保留当时结论。六种构建（四接头模拟、硬接头未知、legacy硬接头）的具体结果及哈希以随包本轮验证结果为准。
