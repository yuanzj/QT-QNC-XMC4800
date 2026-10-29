"""IDE终止后恢复指定XMC的CPU运行，再请求真实UIO恢复从站并核验OP。"""
import argparse
import json
from pathlib import Path
import subprocess
import time
import urllib.request

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--jlink', required=True)
    p.add_argument('--serial', required=True)
    p.add_argument('--url', required=True)
    p.add_argument('--evidence', required=True)
    args = p.parse_args()
    if not args.serial.isdecimal() or not 0 < int(args.serial) < 0xFFFFFFFF:
        raise ValueError('探针序列号无效')
    out = Path(args.evidence).resolve()
    if out.exists(): raise ValueError('证据目录已存在，拒绝覆盖')
    out.mkdir(parents=True)
    script = out / 'resume.jlink'
    script.write_text('exec DisableAutoUpdateFW\nconnect\nIsHalted\ng\nsleep 500\nIsHalted\nexit\n', encoding='ascii')
    with (out / 'resume.log').open('w', encoding='utf-8') as log:
        subprocess.run([args.jlink, '-NoGui', '1', '-ExitOnError', '1', '-SelectEmuBySN', args.serial,
                        '-Device', 'XMC4800-2048', '-If', 'SWD', '-Speed', '1000', '-AutoConnect', '0',
                        '-CommanderScript', str(script)], stdout=log, stderr=subprocess.STDOUT, check=True)
    if 'CPU is not halted.' not in (out / 'resume.log').read_text(encoding='utf-8'):
        raise ValueError('未确认CPU恢复运行，请检查日志')
    opener = urllib.request.build_opener(urllib.request.ProxyHandler({}))
    base = args.url.rstrip('/')
    with opener.open(urllib.request.Request(base + '/api/ecat-recover', data=b'', method='POST'), timeout=6) as r:
        reply = r.read()
        (out / 'recover-response.txt').write_bytes(reply)
        if r.status != 202 or reply != b'slave recover queued\n': raise ValueError('UIO未受理恢复')
    rows = []
    for _ in range(15):
        with opener.open(base + '/api/status', timeout=6) as r: status = json.load(r)
        rows.append(status)
        (out / 'status.json').write_text(json.dumps(rows, indent=2), encoding='utf-8')
        if status['ecat_state'] == 5 and status['ecat_slaves'] == 1 and status['ecat_wkc'] == status['ecat_expected_wkc'] == 3:
            print('CPU已运行；真实EtherCAT已OP，WKC=3/3'); return
        time.sleep(1)
    raise ValueError('UIO尚未恢复OP；保留日志，停止业务测试')

if __name__ == '__main__': main()
