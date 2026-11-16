"""Windows/macOS标准库构建入口：使用固定源码清单，不依赖IDE生成的构建缓存。"""
import argparse
import concurrent.futures
import hashlib
import json
from pathlib import Path
import shutil
import subprocess

ROOT = Path(__file__).resolve().parents[1]

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--gcc', required=True)
    parser.add_argument('--output', required=True)
    parser.add_argument('--scenario', type=int, choices=range(10), default=9,
                        help='逻辑模拟：0正常/1扭矩NOK/2角度NOK/3超时/4同拍故障/5位置边界/6提前20ms故障/7错误36B-TxPDO/8原始整数极值/9独立合成接头；不修改UIO')
    parser.add_argument('--joint', choices=['hard','soft','free-run','jam'], default='hard', help='场景9独立合成夹具，不是实物标定数据')
    parser.add_argument('--velocity', choices=['legacy', 'int64'], default=None,
                        help='场景9默认INT64/1000rpm；物理长度由protocol选择；其他场景默认legacy/40B/500rpm')
    parser.add_argument('--protocol', choices=['legacy', 'qiaotian-20261116'], default=None,
                        help='场景9/INT64默认适配当前UIO的17/46B；legacy保留原12/44B或12/40B')
    parser.add_argument('--model', choices=['simulation','unknown'], default='simulation',
                        help='INT64模式型号信息：SIM-QNC30显式模拟或全零未知；不分配正式型号代码')
    parser.add_argument('--negative-pdo-tail', action='store_true',
                        help='仅MAP-05隔离负例：保留场景9/INT64/模拟型号，只去掉TxPDO最后8B填充，使长度36B而非44B')
    parser.add_argument('--position-test-vector', choices=['off','forward-wrap','reverse-wrap','step-reset'], default='off',
                        help='仅MAP-04协议位置故障输入；不改变独立接头控制/判定，不代表物理质量；默认off')
    parser.add_argument('--sdo-commit-trace', action='store_true',
                        help='默认关闭的完整SDO提交RAM计数；只观察，不改变工艺/反馈/判定')
    args = parser.parse_args()
    int64 = args.velocity == 'int64' if args.velocity else args.scenario == 9
    if int64 and args.scenario != 9: parser.error('INT64仅支持独立场景9；历史协议向量保持旧布局')
    if args.negative_pdo_tail and (args.scenario != 9 or not int64 or args.model != 'simulation'):
        parser.error('隔离长度负例必须保留场景9、INT64及simulation型号')
    if args.position_test_vector != 'off' and (args.scenario != 9 or not int64 or args.model != 'simulation' or args.negative_pdo_tail):
        parser.error('位置故障向量必须保留场景9、INT64、simulation型号和正常PDO长度')
    if args.sdo_commit_trace and (args.scenario != 9 or not int64 or args.model != 'simulation' or args.negative_pdo_tail or args.position_test_vector != 'off'):
        parser.error('SDO提交计数仅用于正常场景9、INT64、simulation型号；不混合故障向量')
    protocol = args.protocol or ('qiaotian-20261116' if int64 and args.scenario == 9 else 'legacy')
    paired = protocol == 'qiaotian-20261116'
    if paired and (not int64 or args.scenario != 9 or args.model != 'simulation' or args.negative_pdo_tail or args.position_test_vector != 'off'):
        parser.error('C21配套仅用于正常场景9/INT64/simulation；负例或未知型号请显式选择legacy')
    gcc = Path(args.gcc).resolve()
    out = Path(args.output).resolve()
    if out.exists(): raise SystemExit('输出已存在，拒绝覆盖')
    out.mkdir(parents=True)
    source = out / 'source'
    shutil.copytree(ROOT, source, ignore=shutil.ignore_patterns('.git', 'build', 'evidence', 'Debug', 'Release', '__pycache__'))
    if paired:
        from c20_profile import apply_profile6, apply_qiaotian
        apply_profile6(source)
        apply_qiaotian(source)
    recipe = json.loads((source / 'tools/source-list.json').read_text(encoding='utf-8'))
    objects = recipe['objects']
    assert len(objects) == len(set(objects))
    includes = ['Libraries/XMCLib/inc', 'Servo_CiA402', 'Libraries/CMSIS/Include',
                'Libraries/CMSIS/Infineon/XMC4800_series/Include', '.', 'Motor_Control',
                'Motion_Control', 'ProbeScope', 'Dave/Generated', 'Libraries']
    arch = ['-mfloat-abi=softfp', '-mfpu=fpv4-sp-d16', '-mcpu=cortex-m4', '-mthumb']
    flags = ['-DXMC4800_F144x2048', '-DFPGA_SIM_SCENARIO=' + str(args.scenario),
             '-DFPGA_TEST_SDO_COMMIT_TRACE=' + str(int(args.sdo_commit_trace)),
             '-DFPGA_TEST_TRUNCATE_TXPDO_TAIL=' + str(int(args.negative_pdo_tail)),
             '-DFPGA_TEST_POSITION_VECTOR=' + str(['off','forward-wrap','reverse-wrap','step-reset'].index(args.position_test_vector)),
             '-DFPGA_SIM_INT64=' + str(int(int64)), '-DFPGA_MODEL_IDENTITY_VALID=' + str(int(args.model == 'simulation')), '-DFPGA_MODEL_PROFILE=' + str(['hard','soft','free-run','jam'].index(args.joint)+1), '-fstack-usage', '-Os', '-g3', '-ffunction-sections', '-fdata-sections', '-Wall', *arch]
    flags.append('-DFPGA_C20_PROFILE=' + str(int(paired)))
    if paired:
        flags.append('-DREVISION_NUMBER=0x060B0901')
    flags += ['-I' + str(source / name) for name in includes]
    commands = []
    for name in objects:
        path = source / Path(name).with_suffix('.c')
        if not path.exists(): path = path.with_suffix('.S')
        if not path.is_file(): raise SystemExit('源码缺失：' + str(path))
        obj = out / 'objects' / name
        obj.parent.mkdir(parents=True, exist_ok=True)
        command = [str(gcc), *flags, *(['-std=gnu99'] if path.suffix == '.c' else ['-x', 'assembler-with-cpp']),
                   '-c', str(path), '-o', str(obj)]
        commands.append({'directory': str(out), 'file': str(path), 'arguments': command})
    (out / 'compile_commands.json').write_text(json.dumps(commands, indent=2), encoding='utf-8')
    def compile_one(item):
        return subprocess.run(item['arguments'], capture_output=True, text=True, errors='replace')
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as pool:
        results = list(pool.map(compile_one, commands))
    with (out / 'build.log').open('w', encoding='utf-8') as log:
        for result in results: log.write(result.stdout + result.stderr)
        if any(result.returncode for result in results): raise SystemExit('编译失败：' + str(out / 'build.log'))
        (out / 'objects.rsp').write_text('\n'.join('"objects/' + n + '"' for n in objects), encoding='utf-8')
        command = [str(gcc), '-T', str(source / 'linker_script.ld'), '-nostartfiles', '-Xlinker', '--gc-sections',
                   '-specs=nano.specs', '-specs=nosys.specs', '-Wl,-Map,xmc4800.map', *arch,
                   '-o', 'xmc4800.elf', '@objects.rsp', '-lm']
        subprocess.run(command, cwd=out, stdout=log, stderr=subprocess.STDOUT, check=True)
        suffix = '.exe' if gcc.suffix == '.exe' else ''
        subprocess.run([str(gcc.parent / ('arm-none-eabi-objcopy' + suffix)), '-O', 'ihex',
                        'xmc4800.elf', 'xmc4800.hex'], cwd=out, stdout=log, stderr=subprocess.STDOUT, check=True)
    from flash import read_hex, validate_image
    validate_image(read_hex(out / 'xmc4800.hex'), paired)
    inputs = {p.relative_to(source).as_posix(): sha(p) for p in sorted(source.rglob('*')) if p.is_file()}
    manifest = {'device': 'XMC4800-2048', 'example': 'expert-logic-model-v2', 'scenario': args.scenario, 'inputs': inputs,
                'protocol': protocol, 'paired_id': '0x20261116' if paired else None,
                'rx_pdo_bytes': 17 if paired else 12,
                'nvm_reserved': ['0x0C004000', '0x0C00C000'] if paired else None,
                'feedback_source': 'synthetic-independent-joint' if args.scenario==9 else 'synthetic-protocol-vector',
                'position_test_vector': args.position_test_vector,
                'sdo_commit_trace': args.sdo_commit_trace,
                'position_source': 'synthetic-protocol-fault-vector' if args.position_test_vector != 'off' else 'model',
                'joint_profile': args.joint if args.scenario==9 else None, 'physical_calibration': False, 'velocity_mode': 'int64' if int64 else 'legacy',
                'tool_model_object': '0x2214:00' if int64 else None,
                'tool_model': 'SIM-QNC30' if int64 and args.model == 'simulation' else None,
                'tool_model_source': 3 if int64 and args.model == 'simulation' else 0,
                'official_model_code_assigned': False,
                'velocity_bits': 64 if int64 else 32, 'tx_pdo_bytes': 46 if paired else (36 if args.negative_pdo_tail else (44 if int64 else (36 if args.scenario==7 else 40))),
                'test_only_negative_mapping': args.negative_pdo_tail, 'negative_pdo_tail_bytes': 8 if args.negative_pdo_tail else 0,
                'velocity_object': '0x2F00:04' if paired else ('0x2212:00' if int64 else '0x606C:00'),
                'required_uio_pdo_map_ver': 4 if int64 else None,
                'max_speed_rpm': 1000 if int64 else 500,
                'compiler': subprocess.check_output([str(gcc), '--version'], text=True).splitlines()[0],
                'recipe_sha256': sha(Path(__file__)),
                'artifacts': {n: sha(out / n) for n in ['xmc4800.elf', 'xmc4800.hex']}}
    (out / 'build.manifest.json').write_text(json.dumps(manifest, indent=2), encoding='utf-8')
    print('构建通过：' + str(out))

if __name__ == '__main__': main()
