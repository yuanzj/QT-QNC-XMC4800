"""XMC4800定向刷写：完整备份、保留擦除扇区空洞、SII不写、全片回读核对。"""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess

BASE = 0x0C000000

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def read_hex(path):
    memory = {}
    upper = 0
    ended = False
    for line in path.read_text(encoding='ascii').splitlines():
        if ended or not line.startswith(':'): raise ValueError('HEX顺序错误')
        row = bytes.fromhex(line[1:])
        if len(row) != row[0] + 5 or sum(row) % 256: raise ValueError('HEX校验错误')
        n, kind = row[0], row[3]
        offset = int.from_bytes(row[1:3], 'big')
        if kind == 4 and n == 2:
            upper = int.from_bytes(row[4:6], 'big') << 16
        elif kind == 0:
            for i, byte in enumerate(row[4:-1]):
                address = upper + offset + i
                if not (BASE <= address < BASE + 0x10000 or BASE + 0x20000 <= address < BASE + 0x40000):
                    raise ValueError('镜像超出本例应用扇区或覆盖SII')
                if address in memory: raise ValueError('HEX地址重复')
                memory[address] = byte
        elif kind == 1 and n == 0:
            ended = True
        elif kind != 5: raise ValueError('不支持的HEX记录')
    if not ended or BASE not in memory: raise ValueError('启动向量或EOF缺失')
    return memory

def record(address, kind, data):
    row = bytes([len(data), address >> 8, address & 255, kind]) + data
    return ':' + (row + bytes([(-sum(row)) & 255])).hex().upper()

def validate_image(memory, paired):
    """固件不得占用配套日志及SII；整扇区保全文件另按备份核对。"""
    if paired and any(BASE + 0x4000 <= address < BASE + 0x20000 for address in memory):
        raise ValueError('C20配套固件覆盖预留日志或SII区域')

def write_preserved_hex(path, image):
    lines = []
    # XMC4800前四个16KiB扇区及0x20000起的128KiB应用扇区；跳过64KiB EEPROM。
    for start, end in [(0, 0x10000), (0x20000, 0x40000)]:
        for offset in range(start, end, 32):
            address = BASE + offset
            if offset == start or address & 0xFFFF == 0:
                lines.append(record(0, 4, (address >> 16).to_bytes(2, 'big')))
            lines.append(record(address & 0xFFFF, 0, image[offset:offset + 32]))
    lines.append(record(0, 1, b''))
    path.write_text('\n'.join(lines) + '\n', encoding='ascii')

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--build', required=True)
    p.add_argument('--jlink', required=True)
    p.add_argument('--serial', required=True)
    p.add_argument('--evidence', required=True)
    p.add_argument('--confirm', action='store_true')
    args = p.parse_args()
    build = Path(args.build).resolve()
    evidence = Path(args.evidence).resolve()
    if not args.serial.isdecimal() or int(args.serial) <= 0: raise ValueError('探针序列号无效')
    if any(c in str(build) + str(evidence) for c in '\r\n"'): raise ValueError('路径包含非法字符')
    if evidence.exists(): raise ValueError('证据目录已存在，拒绝覆盖')
    manifest = json.loads((build / 'build.manifest.json').read_text())
    for name, expected in manifest['artifacts'].items():
        if sha(build / name) != expected: raise ValueError('制品摘要变化')
    for name, expected in manifest['inputs'].items():
        path = (build / 'source' / name).resolve()
        if not path.is_relative_to(build / 'source') or sha(path) != expected: raise ValueError('构建快照变化')
    memory = read_hex(build / 'xmc4800.hex')
    validate_image(memory, manifest.get('protocol') in ('qiaotian-20261109', 'qiaotian-20261116'))
    evidence.mkdir(parents=True)
    (evidence / 'plan.json').write_text(json.dumps({'serial': args.serial, 'device': 'XMC4800-2048',
        'image_bytes': len(memory), 'sii_written': False, 'sector_holes_preserved': True,
        'hex_sha256': sha(build / 'xmc4800.hex')}, indent=2), encoding='utf-8')
    if not args.confirm:
        print('预览完成，未连接设备：' + str(evidence)); return
    command = [args.jlink, '-NoGui', '1', '-ExitOnError', '1', '-SelectEmuBySN', args.serial,
               '-Device', 'XMC4800-2048', '-If', 'SWD', '-Speed', '1000', '-AutoConnect', '0']
    def run(name, commands):
        script = evidence / (name + '.jlink')
        script.write_text('\n'.join(['exec DisableAutoUpdateFW', *commands, 'exit']) + '\n', encoding='utf-8')
        with (evidence / (name + '.log')).open('w', encoding='utf-8') as log:
            subprocess.run([*command, '-CommanderScript', str(script)], stdout=log, stderr=subprocess.STDOUT, check=True)
    run('backup', ['connect', 'h', 'mem32 0x50004004 1',
                  'savebin "' + str(evidence / 'before.bin') + '" 0x0C000000 0x200000'])
    before = (evidence / 'before.bin').read_bytes()
    if len(before) != 0x200000 or '50004004 = 00048001' not in (evidence / 'backup.log').read_text():
        raise ValueError('备份或芯片身份无效，停止；目标可能暂停')
    expected = bytearray(before)
    for address, value in memory.items(): expected[address - BASE] = value
    write_preserved_hex(evidence / 'preserved.hex', expected)
    preserved = read_hex(evidence / 'preserved.hex')
    assert len(preserved) == 0x30000
    (evidence / 'expected-full.bin').write_bytes(expected)
    run('program', ['connect', 'h', 'loadfile "' + str(evidence / 'preserved.hex') + '"',
                    'savebin "' + str(evidence / 'after.bin') + '" 0x0C000000 0x200000'])
    after = (evidence / 'after.bin').read_bytes()
    passed = after == expected
    result = {'full_readback_matches': passed, 'sii_preserved': after[0x10000:0x20000] == before[0x10000:0x20000],
              'nvm_preserved': after[0x4000:0xC000] == before[0x4000:0xC000],
              'image_bytes': len(memory), 'before_sha256': sha(evidence / 'before.bin'),
              'after_sha256': sha(evidence / 'after.bin'), 'cpu_running': False}
    (evidence / 'result.json').write_text(json.dumps(result, indent=2), encoding='utf-8')
    if not passed: raise ValueError('完整回读不一致，停止；保留暂停状态和失败日志')
    # 全镜像核对之后才恢复CPU，不在校验失败时先运行未知镜像。
    run('resume', ['connect', 'r', 'g', 'sleep 500', 'IsHalted'])
    result['cpu_running'] = 'CPU is not halted.' in (evidence / 'resume.log').read_text()
    (evidence / 'result.json').write_text(json.dumps(result, indent=2), encoding='utf-8')
    if not result['cpu_running']: raise ValueError('未获得恢复运行证据')
    print(json.dumps(result, indent=2))

if __name__ == '__main__': main()
