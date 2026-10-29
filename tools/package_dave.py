"""封存已完成的 DAVE Debug/Release 制品，交给同一保留扇区刷写入口。"""
import argparse
import json
from pathlib import Path
import shutil
import subprocess
from build import ROOT, sha

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--configuration', choices=['Debug', 'Release'], default='Debug')
    p.add_argument('--gcc', required=True)
    p.add_argument('--output', required=True)
    args = p.parse_args()
    gcc = Path(args.gcc).resolve()
    out = Path(args.output).resolve()
    if out.exists(): raise ValueError('输出已存在，拒绝覆盖')
    native = ROOT / args.configuration
    name = 'DOCH_ECAT_XMC48_Servo_Probe_20261018'
    elf, ihex = native / (name + '.elf'), native / (name + '.hex')
    if not elf.is_file() or not ihex.is_file(): raise ValueError('请先在DAVE完成编译')
    # 防止把较新源码与较旧ELF封存为同一次构建。
    units = json.loads((ROOT / 'tools/source-list.json').read_text(encoding='utf-8'))['objects']
    for unit in units:
        obj = native / unit
        src = (ROOT / unit).with_suffix('.c')
        if not src.exists(): src = src.with_suffix('.S')
        if not obj.is_file() or src.stat().st_mtime > obj.stat().st_mtime or obj.stat().st_mtime > elf.stat().st_mtime:
            raise ValueError('源码/对象/ELF时间不一致，请重新构建：' + unit)
    out.mkdir(parents=True)
    shutil.copytree(ROOT, out / 'source', ignore=shutil.ignore_patterns('.git', 'Debug', 'Release', 'build', 'evidence', '__pycache__'))
    shutil.copy2(elf, out / 'xmc4800.elf')
    suffix = '.exe' if gcc.suffix == '.exe' else ''
    subprocess.run([str(gcc.parent / ('arm-none-eabi-objcopy' + suffix)), '-O', 'ihex', str(elf), str(out / 'xmc4800.hex')], check=True)
    if sha(ihex) != sha(out / 'xmc4800.hex'): raise ValueError('IDE HEX与ELF重新导出不一致')
    shutil.copytree(native, out / 'native-build')
    source = out / 'source'
    manifest = {'device': 'XMC4800-2048', 'example': 'expert-logic-model-v2',
                'origin': 'DAVE-4.5.0/' + args.configuration,
                'compiler': subprocess.check_output([str(gcc), '--version'], text=True).splitlines()[0],
                'inputs': {f.relative_to(source).as_posix(): sha(f) for f in sorted(source.rglob('*')) if f.is_file()},
                'artifacts': {n: sha(out / n) for n in ['xmc4800.elf', 'xmc4800.hex']}}
    (out / 'build.manifest.json').write_text(json.dumps(manifest, indent=2), encoding='utf-8')
    print(json.dumps({k: v for k, v in manifest.items() if k != 'inputs'}, indent=2))

if __name__ == '__main__': main()
