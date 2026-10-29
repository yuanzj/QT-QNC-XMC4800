"""Windows/macOS标准库构建入口：读取客户对象顺序，新增两个隔离模块，不执行旧Makefile。"""
import argparse
import concurrent.futures
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess

ROOT = Path(__file__).resolve().parents[1]

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--gcc', required=True)
    parser.add_argument('--output', required=True)
    args = parser.parse_args()
    gcc = Path(args.gcc).resolve()
    out = Path(args.output).resolve()
    if out.exists(): raise SystemExit('输出已存在，拒绝覆盖')
    out.mkdir(parents=True)
    source = out / 'source'
    shutil.copytree(ROOT, source, ignore=shutil.ignore_patterns('.git', 'build', 'evidence', '__pycache__'))
    objects = []
    graph = (source / 'Release/makefile').read_text(errors='replace')
    for include in re.findall(r'^-include ([^\s]+\.mk)$', graph, re.M):
        path = source / 'Release' / include
        if path.exists():
            objects += re.findall(r'^\./([^\s]+\.o)\s*\\?\s*$', path.read_text(errors='replace'), re.M)
    objects += ['FpgaSim/fpga_sim.o', 'Simulation/ethercat_adapter.o']
    assert len(objects) == len(set(objects))
    includes = ['Libraries/XMCLib/inc', 'Servo_CiA402', 'Libraries/CMSIS/Include',
                'Libraries/CMSIS/Infineon/XMC4800_series/Include', '.', 'Motor_Control',
                'Motion_Control', 'ProbeScope', 'Dave/Generated', 'Libraries']
    arch = ['-mfloat-abi=softfp', '-mfpu=fpv4-sp-d16', '-mcpu=cortex-m4', '-mthumb']
    flags = ['-DXMC4800_F144x2048', '-Os', '-g3', '-ffunction-sections', '-fdata-sections', '-Wall', *arch]
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
    manifest = {'device': 'XMC4800-2048', 'example': 'single-wait-v1', 'inputs': inputs,
                'compiler': subprocess.check_output([str(gcc), '--version'], text=True).splitlines()[0],
                'recipe_sha256': sha(Path(__file__)),
                'artifacts': {n: sha(out / n) for n in ['xmc4800.elf', 'xmc4800.hex']}}
    (out / 'build.manifest.json').write_text(json.dumps(manifest, indent=2), encoding='utf-8')
    print('构建通过：' + str(out))

if __name__ == '__main__': main()
