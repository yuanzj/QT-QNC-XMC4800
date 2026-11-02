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
                        help='场景9默认int64/44B/1000rpm；其他场景默认legacy/40B/500rpm')
    args = parser.parse_args()
    int64 = args.velocity == 'int64' if args.velocity else args.scenario == 9
    if int64 and args.scenario != 9: parser.error('INT64仅支持独立场景9；历史协议向量保持旧布局')
    gcc = Path(args.gcc).resolve()
    out = Path(args.output).resolve()
    if out.exists(): raise SystemExit('输出已存在，拒绝覆盖')
    out.mkdir(parents=True)
    source = out / 'source'
    shutil.copytree(ROOT, source, ignore=shutil.ignore_patterns('.git', 'build', 'evidence', 'Debug', 'Release', '__pycache__'))
    recipe = json.loads((source / 'tools/source-list.json').read_text(encoding='utf-8'))
    objects = recipe['objects']
    assert len(objects) == len(set(objects))
    includes = ['Libraries/XMCLib/inc', 'Servo_CiA402', 'Libraries/CMSIS/Include',
                'Libraries/CMSIS/Infineon/XMC4800_series/Include', '.', 'Motor_Control',
                'Motion_Control', 'ProbeScope', 'Dave/Generated', 'Libraries']
    arch = ['-mfloat-abi=softfp', '-mfpu=fpv4-sp-d16', '-mcpu=cortex-m4', '-mthumb']
    flags = ['-DXMC4800_F144x2048', '-DFPGA_SIM_SCENARIO=' + str(args.scenario),
             '-DFPGA_SIM_INT64=' + str(int(int64)), '-DFPGA_MODEL_PROFILE=' + str(['hard','soft','free-run','jam'].index(args.joint)+1), '-fstack-usage', '-Os', '-g3', '-ffunction-sections', '-fdata-sections', '-Wall', *arch]
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
    inputs = {p.relative_to(source).as_posix(): sha(p) for p in sorted(source.rglob('*')) if p.is_file()}
    manifest = {'device': 'XMC4800-2048', 'example': 'expert-logic-model-v2', 'scenario': args.scenario, 'inputs': inputs,
                'feedback_source': 'synthetic-independent-joint' if args.scenario==9 else 'synthetic-protocol-vector',
                'joint_profile': args.joint if args.scenario==9 else None, 'physical_calibration': False, 'velocity_mode': 'int64' if int64 else 'legacy',
                'velocity_bits': 64 if int64 else 32, 'tx_pdo_bytes': 44 if int64 else (36 if args.scenario==7 else 40),
                'velocity_object': '0x2212:00' if int64 else '0x606C:00',
                'required_uio_pdo_map_ver': 4 if int64 else None,
                'max_speed_rpm': 1000 if int64 else 500,
                'compiler': subprocess.check_output([str(gcc), '--version'], text=True).splitlines()[0],
                'recipe_sha256': sha(Path(__file__)),
                'artifacts': {n: sha(out / n) for n in ['xmc4800.elf', 'xmc4800.hex']}}
    (out / 'build.manifest.json').write_text(json.dumps(manifest, indent=2), encoding='utf-8')
    print('构建通过：' + str(out))

if __name__ == '__main__': main()
