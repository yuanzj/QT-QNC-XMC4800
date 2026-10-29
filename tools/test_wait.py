"""通过真实UIO的现有SDO/PDO业务入口运行单步等待；不通过SWD伪造反馈。"""
import argparse
import datetime
import json
from pathlib import Path
import struct
import time
import urllib.error
import urllib.request
import zlib

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--url', required=True)
    p.add_argument('--evidence', required=True)
    p.add_argument('--repeat', type=int, default=3)
    args = p.parse_args()
    if not 1 <= args.repeat <= 10: raise ValueError('repeat须在1..10')
    evidence = Path(args.evidence).resolve()
    if evidence.exists(): raise ValueError('证据目录已存在')
    evidence.mkdir(parents=True)
    opener = urllib.request.build_opener(urllib.request.ProxyHandler({}))
    base = args.url.rstrip('/')
    rows = []
    def request(path, body=None):
        method = 'POST' if body is not None else 'GET'
        req = urllib.request.Request(base + path, data=body, method=method,
                                     headers={'Content-Type': 'application/octet-stream'})
        with opener.open(req, timeout=6) as response:
            raw = response.read()
            row = {'time': datetime.datetime.now().astimezone().isoformat(), 'method': method,
                   'path': path, 'http': response.status, 'body': raw.decode('utf-8')}
        rows.append(row)
        (evidence / 'http.ndjson').write_text('\n'.join(json.dumps(r, ensure_ascii=False) for r in rows) + '\n', encoding='utf-8')
        if method == 'POST':
            if row['http'] != 202 or raw != b'xmc job accepted\n':
                raise ValueError('UIO没有按约定受理任务')
            return {'accepted': True}
        if row['http'] != 200:
            raise ValueError('UIO读取状态失败')
        return json.loads(raw)
    baseline = request('/api/status')
    if baseline['ecat_state'] != 5 or baseline['ecat_wkc'] != baseline['ecat_expected_wkc']:
        raise ValueError('真实EtherCAT未OP或WKC不匹配')
    # PSET7，专家模式，1步；WAIT帧13B，时间型，1000ms，上限2000ms，失败停止。
    pset = bytes([7, 2, 1, 4, 13, 0, 0]) + struct.pack('<H', 1000) + b'\0\0' + struct.pack('<H', 2000) + b'\0\0\2'
    assert len(pset) == 16
    (evidence / 'pset.bin').write_bytes(pset)
    expected_crc = zlib.crc32(pset)
    results = []
    for attempt in range(args.repeat):
        submitted = request('/api/xmc-job', pset)
        deadline = time.monotonic() + 10
        seen_running = False
        while time.monotonic() < deadline:
            snap = request('/api/xmc-job')
            if snap['state'] == 3 and snap['pset_echo'] == 0x0701: seen_running = True
            if snap['state'] in (4, 5): break
            time.sleep(0.05)
        else: raise ValueError('业务超时，原始记录保留')
        result = {'attempt': attempt + 1, 'seen_running': seen_running, 'final': snap,
                  'passed': seen_running and snap['state'] == 4 and snap['error'] == 0 and
                    snap['last_step_result'] == 1 and snap['pset_echo'] == 0x0700 and
                    snap['pset_verify'] == 1 and snap['pset_len'] == 16 and
                    int(snap['pset_crc'], 16) == expected_crc and 900 <= snap['elapsed_ms'] <= 2500}
        results.append(result)
        (evidence / 'result.json').write_text(json.dumps({'expected_crc': f'{expected_crc:08x}', 'runs': results}, indent=2), encoding='utf-8')
        if not result['passed']: raise ValueError('等待业务断言失败，保留原始记录')
    final = request('/api/status')
    summary = {'runs_passed': len(results), 'expected_crc': f'{expected_crc:08x}',
               'wkc_errors_added': final['ecat_wkc_errors'] - baseline['ecat_wkc_errors'],
               'cycles_added': final['ecat_cycles'] - baseline['ecat_cycles'],
               'rpmsg_drops_added': final['rpmsg_dropped'] - baseline['rpmsg_dropped'],
               'coverage': 'UIO-SDO-XMC-FpgaSim-PDO-UIO; not HMI G1 acceptance'}
    (evidence / 'summary.json').write_text(json.dumps(summary, indent=2), encoding='utf-8')
    print(json.dumps(summary, indent=2))

if __name__ == '__main__': main()
