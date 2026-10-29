"""按客户本机DAVE/J-Link路径和指定XMC探针生成IDE调试配置，不连接硬件。"""
import argparse
from pathlib import Path
import xml.etree.ElementTree as E

ROOT = Path(__file__).resolve().parents[1]

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--dave', required=True, help='DAVE-4.5.0目录，内含eclipse')
    p.add_argument('--jlink-server', required=True)
    p.add_argument('--serial', required=True)
    p.add_argument('--output', default='XMC4800-WAIT-Attach.local.launch')
    args = p.parse_args()
    if not args.serial.isdecimal() or not 0 < int(args.serial) < 0xFFFFFFFF:
        raise ValueError('请指定XMC板独立且有效的探针序列号')
    gdb = Path(args.dave).resolve() / 'eclipse/ARM-GCC-49/bin/arm-none-eabi-gdb.exe'
    server = Path(args.jlink_server).resolve()
    for exe in [gdb, server]:
        if not exe.is_file(): raise ValueError('程序不存在：' + str(exe))
    out = (ROOT / args.output).resolve()
    if out.parent != ROOT or not out.name.endswith('.local.launch'):
        raise ValueError('输出须位于工程根目录并以.local.launch结尾')
    if out.exists(): raise ValueError('配置已存在；请指定新的--output以保留旧配置')
    tree = E.parse(ROOT / 'tools/dave-attach.launch.template')
    values = {'@GDB@': gdb.as_posix(), '@JLINK_SERVER@': server.as_posix(), '@SERIAL@': args.serial}
    for e in tree.getroot():
        if e.get('value') in values: e.set('value', values[e.get('value')])
    tree.write(out, encoding='utf-8', xml_declaration=True)
    print('已生成（未连接硬件）：' + str(out))

if __name__ == '__main__': main()
