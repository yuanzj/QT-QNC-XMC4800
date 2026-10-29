"""UIO诊断入口→真实SDO/PDO→模型；不替代HMI首颗或五类工步验收。"""
import argparse
import datetime
import json
from pathlib import Path
import struct
import time
import urllib.error
import urllib.request
import zlib

def snug(direction=0):
    s = bytearray(61)
    s[0] = 3
    struct.pack_into('<H', s, 1, 61)
    s[3] = 1
    for offset, value in [(4, 11000), (8, 12000), (12, 10000), (24, 1000),
                          (28, 1400), (36, 1200), (41, 100000)]:
        struct.pack_into('<I', s, offset, value)
    s[40] = direction
    s[49] = s[50] = 1
    struct.pack_into('<H', s, 51, 2000)
    s[55] = s[56] = 2
    return bytes(s)

def wait(milliseconds):
    return bytes([4, 13, 0, 0]) + struct.pack('<H', milliseconds) + b'\0\0' + struct.pack('<H', 5000) + b'\0\0\2'

def multistep():
    identify = bytearray(22)
    identify[0] = 1
    struct.pack_into('<H', identify, 1, 22)
    struct.pack_into('<I', identify, 3, 3300)
    struct.pack_into('<I', identify, 15, 1200)
    rundown = bytearray(36)
    rundown[0] = 2
    struct.pack_into('<H', rundown, 1, 36)
    rundown[3] = 1
    struct.pack_into('<I', rundown, 10, 5500)
    struct.pack_into('<H', rundown, 14, 2000)
    rundown[18] = 2
    rundown[19] = 1
    struct.pack_into('<I', rundown, 24, 2400)
    release = bytearray(26)
    release[0] = 5
    struct.pack_into('<H', release, 1, 26)
    struct.pack_into('<I', release, 11, 600)
    struct.pack_into('<H', release, 21, 2000)
    release[25] = 2
    return [bytes(identify), bytes(rundown), snug(), wait(100), bytes([6, 5, 0, 0, 0]), bytes(release)]

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--url', required=True)
    p.add_argument('--evidence', required=True)
    p.add_argument('--frames', help='未改写TCP抓包器的frames.ndjson；多工步必须提供，不能靠HTTP轮询证明短工步')
    p.add_argument('--scenario', type=int, choices=range(5), default=0)
    p.add_argument('--repeat', type=int, choices=range(1, 4), default=3)
    p.add_argument('--which', choices=['all', 'snug', 'reverse', 'multi', 'sixteen', 'wait'], default='all')
    args = p.parse_args()
    capture = Path(args.frames).resolve() if args.frames else None
    if args.which in ('all', 'multi', 'sixteen') and capture is None:
        raise ValueError('多工步需连续报文证据')
    out = Path(args.evidence).resolve()
    out.mkdir(parents=True, exist_ok=False)
    http = urllib.request.build_opener(urllib.request.ProxyHandler({}))
    def call(path, body=None):
        q = urllib.request.Request(args.url.rstrip('/') + path, data=body,
            method='GET' if body is None else 'POST', headers={'Content-Type': 'application/octet-stream'})
        try:
            with http.open(q, timeout=6) as r: code, raw = r.status, r.read()
        except urllib.error.HTTPError as e: code, raw = e.code, e.read()
        with (out / 'http.ndjson').open('a', encoding='utf-8') as log:
            log.write(json.dumps({'time': datetime.datetime.now().astimezone().isoformat(),
                'mono_ns': time.monotonic_ns(), 'path': path, 'status': code,
                'request_hex': None if body is None else body.hex(), 'body': raw.decode(errors='replace')}) + '\n')
        if body is not None: return code, raw
        if code != 200: raise ValueError('诊断读取失败：' + path)
        return json.loads(raw)
    before = call('/api/status')
    if before['ecat_state'] != 5 or before['ecat_wkc'] != before['ecat_expected_wkc']:
        raise ValueError('真实总线未OP；先恢复再测')
    vectors = {'snug': (101, [snug()], 366, 8388608),
               'reverse': (102, [snug(1)], -366, -8388608),
               'multi': (103, multistep(), 0, -4194304),
               'sixteen': (104, [snug()] * 16, 366, 8388608),
               'wait': (105, [wait(500)], 0, 0)}
    names = list(vectors) if args.which == 'all' else [args.which]
    if args.scenario and args.which != 'snug': raise ValueError('异常固件仅执行独立snug分支')
    results = []
    for name in names:
        number, steps, torque, position = vectors[name]
        data = bytes([number, 2, len(steps)]) + b''.join(steps)
        (out / (name + '.bin')).write_bytes(data)
        for repeat in range(args.repeat):
            capture_offset = capture.stat().st_size if capture else 0
            accepted, response = call('/api/xmc-job', data)
            if accepted != 202 or response != b'xmc job accepted\n': raise ValueError('任务未受理')
            seen = set()
            deadline = time.monotonic() + 40
            while time.monotonic() < deadline:
                status = call('/api/xmc-job')
                if status['state'] == 3 and status['current_step']: seen.add(status['current_step'])
                if status['state'] in (4, 5): break
                time.sleep(0.02)
            else: raise ValueError('模拟运行超时')
            wire_steps, events = set(), []
            if capture:
                # 结果HTTP状态可能先于TCP尾事件送达；短工步按连续流核对，不延长固件来迎合轮询。
                time.sleep(0.4)
                with capture.open('rb') as stream:
                    stream.seek(capture_offset)
                    for line in stream.read().splitlines():
                        try: frame = json.loads(line)
                        except ValueError: continue  # 正在追加的最后一行留在原始文件，不能据此补造证据。
                        if frame.get('kind') != 'frame' or frame.get('direction') != 'uio-to-hmi': continue
                        if not frame['crc_ok']: raise ValueError('抓包CRC无效')
                        raw = bytes.fromhex(frame['payload_hex'])
                        if frame['type'] == '0201':
                            for offset in range(24, len(raw), 40):
                                if raw[offset + 21] == number and raw[offset + 22]: wire_steps.add(raw[offset + 22])
                        if frame['type'] == '4302' and int.from_bytes(raw[16:20], 'little') == status['cyc_seq']:
                            events.append({'step': raw[24], 'type': raw[25], 'result': raw[26]})
            expected_state = 5 if args.scenario else 4
            passed = status['state'] == expected_state and status['pset_verify'] == 1 and \
                status['pset_len'] == len(data) and int(status['pset_crc'], 16) == zlib.crc32(data) and bool(seen)
            if not args.scenario:
                passed = passed and status['step_result'] == 1 and status['torque'] == torque and \
                    status['position'] == position
                if capture:
                    passed = passed and wire_steps == set(range(1, len(steps) + 1)) and \
                        [e['step'] for e in events] == list(range(1, len(steps) + 1)) and all(e['result'] == 1 for e in events)
            else:
                passed = passed and status['step_result'] == 0
                if args.scenario == 1: passed = passed and status['torque'] == 433
                if args.scenario == 2: passed = passed and status['position'] == 10485760
                if args.scenario == 4: passed = passed and status['status_code'] == 0x7001
            results.append({'name': name, 'repeat': repeat + 1, 'passed': passed,
                'seen_steps': sorted(seen), 'final': status})
            results[-1].update({'wire_steps': sorted(wire_steps), 'step_events': events})
            (out / 'result.json').write_text(json.dumps(results, indent=2), encoding='utf-8')
            print(name, repeat + 1, 'PASS' if passed else 'FAIL', 'steps', sorted(seen),
                'ms', status['elapsed_ms'], 'torque', status['torque'], 'position', status['position'], flush=True)
            if not passed: raise ValueError('独立预期与实板反馈不符，保留失败')
    after = call('/api/status')
    summary = {'runs': len(results), 'scenario': args.scenario,
        'wkc_errors_added': after['ecat_wkc_errors'] - before['ecat_wkc_errors'],
        'rpmsg_drops_added': after['rpmsg_dropped'] - before['rpmsg_dropped'],
        'coverage': 'UIO诊断入口+真实SDO/PDO+4800逻辑模型；不签HMI首颗/真实算法/实际DO'}
    (out / 'summary.json').write_text(json.dumps(summary, ensure_ascii=False, indent=2), encoding='utf-8')
    print(json.dumps(summary, ensure_ascii=False))

if __name__ == '__main__': main()
