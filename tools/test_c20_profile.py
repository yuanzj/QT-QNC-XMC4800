"""本机验证C21配套接口、日志和独立接头执行；不接入设备。"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]

def function(source, name):
    start = source.index(name + '(')
    start = source.rfind('\n', 0, start) + 1
    brace = source.index('{', start)
    depth = 0
    for end in range(brace, len(source)):
        depth += (source[end] == '{') - (source[end] == '}')
        if not depth:
            return source[start:end + 1] + '\n'
    raise ValueError('函数不完整：' + name)

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--cc', default='clang')
    p.add_argument('--output', required=True)
    p.add_argument('--uio-root', type=Path, help='只读编译当前UIO的生产配套解码、事件模块及宿主边界')
    args = p.parse_args()
    out = Path(args.output).resolve()
    out.mkdir(parents=True, exist_ok=False)
    # Remove only the observation additions and verify the frozen old executor.
    origin = json.loads((ROOT / 'Simulation/c20-origin.json').read_text())
    current = (ROOT / 'FpgaSim/fpga_control_model.c').read_text()
    baseline, count = re.subn(r'^#if FPGA_C20_PROFILE /\* runtime observation \*/\n.*?^#endif /\* runtime observation \*/\n', '', current, flags=re.M | re.S)
    if count != 3:
        raise ValueError('执行器观察代码边界不匹配')
    baseline = baseline.replace('    while(delta--){\n        ++r->last_tick_ms;tick_one(r,r->last_tick_ms,now,permitted);\n    }',
                                '    while(delta--){++r->last_tick_ms;tick_one(r,r->last_tick_ms,now,permitted);}')
    baseline_sha = hashlib.sha256(baseline.encode()).hexdigest()
    if baseline_sha != origin['pre_timing_observation_sha256']['FpgaSim/fpga_control_model.c']:
        raise ValueError('观察代码之外的原控制逻辑发生变化')
    for name, expected in origin['preserved_model_sha256'].items():
        if hashlib.sha256((ROOT / name).read_bytes()).hexdigest() != expected:
            raise ValueError('独立模型保护文件变化: ' + name)
    (out / 'pre_observation_executor.inc').write_text(baseline)
    ssc = (ROOT / 'SSC/Src/QiaoTian_XMC_Servo.c').read_text()
    (out / 'c20_ethercat_functions.inc').write_text(''.join(function(ssc, n) for n in [
        'APPL_InputMapping', 'APPL_OutputMapping', 'App_Run_IsPermitted', 'App_Storage_Poll']))
    header = (ROOT / 'SSC/Src/sdoserv.h').read_text()
    (out / 'c20_abort_codes.h').write_text('\n'.join(re.findall(r'^#define\s+ABORTIDX_\w+\s+\S+', header, re.M)) + '\n')
    common = ['-std=c99', '-Wall', '-Wextra', '-Werror', '-UNDEBUG', '-fsanitize=address,undefined',
              '-DFPGA_C20_PROFILE=1', '-DFPGA_SIM_INT64=1', '-I' + str(ROOT), '-I' + str(ROOT / 'FpgaSim'), '-I' + str(out)]
    uio_reference = None
    uio_sources = []
    uio_flags = []
    if args.uio_root:
        uio_root = args.uio_root.resolve()
        header = uio_root / 'firmware/rt1176/cores/cm7/ethercat/ethercat_qiaotian_paired.h'
        common.append('-DQNC_UIO_PAIRED_HEADER="' + str(header) + '"')
        uio_reference = {'head': subprocess.check_output(['git', '-C', str(uio_root), 'rev-parse', 'HEAD'], text=True).strip(),
                         'paired_header_sha256': hashlib.sha256(header.read_bytes()).hexdigest()}
        softbus = uio_root / 'firmware/rt1176/shared/softbus'
        cm7 = uio_root / 'firmware/rt1176/cores/cm7'
        adapter = (softbus / 'adapters/uio_hmi_adapter.c').read_text()
        begin = adapter.index('static __attribute__((noinline)) uint64_t local_epoch_ms(')
        end = adapter.index('static uint64_t epoch_ms(void)', begin)
        begin2 = adapter.index('static uint64_t pdo_epoch_ms_from_monotonic(uint64_t monotonic_us)')
        end2 = adapter.index('static void pdo_note_cycle_advanced(', begin2)
        (out / 'pdo_clock.inc').write_text(adapter[begin:end] + adapter[begin2:end2])
        decode = function((cm7 / 'ethercat/ethercat_xmc_protocol.c').read_text(), 'ethercat_xmc_decode_tx')
        (out / 'c21_uio_decode.inc').write_text(decode.replace('void ethercat_xmc_decode_tx(', 'void review_decode_tx('))
        uio_sources = [ROOT / 'tests/c21_uio_bridge.c', cm7 / 'ethercat/ethercat_xmc_hmi_frame.c',
                       softbus / 'codec/uio_hmi_protocol.c']
        uio_flags = ['-std=c11', '-DUIO_HMI_WIRE_VERSION=6', '-DUIO_PSET_FLASH_VIRTUAL=1', '-DQNC_UIO_PIPELINE=1']
        uio_flags += ['-I' + str(p) for p in [cm7, softbus / 'include', softbus / 'generated',
                      softbus / 'ports/rt1176', softbus / 'tests/host_sim/rtos', softbus / 'tests']]
    model = ['FpgaSim/fpga_program.c', 'FpgaSim/feedback_model.c', 'FpgaSim/fpga_control_model.c',
             'Simulation/native_causal_pset.c']
    cases = [('c21-storage-runtime', ['tests/test_c21_storage_runtime.c', 'Simulation/ethercat_adapter.c', *model]),
             ('c21-compatibility', ['tests/test_c21_compatibility.c', 'Simulation/ethercat_adapter.c', *model]),
             ('integration', ['tests/test_c20_integration.c', 'Simulation/ethercat_adapter.c', *model]),
             ('nvm', ['tests/test_c20_nvm.c']),
             ('model-hmi', ['tests/test_hmi_pset.c', *model]),
             ('identify-actions', ['tests/test_c20_identify_actions.c', *model]),
             ('model-engage', ['tests/test_engage_loosen.c', *model]),
             ('model-deceleration', ['tests/test_deceleration.c', *model]),
             ('model-rundown', ['tests/test_rundown_torque.c', *model])]
    cases += [('causal-profile-' + str(profile), ['tests/test_causal_model.c', *model])
              for profile in range(1, 5)]
    cases += [('observer-equivalence-' + str(profile), ['tests/test_c21_tick_observer.c', *model])
              for profile in range(1, 5)]
    results = []
    env = {**os.environ, 'UBSAN_OPTIONS': 'halt_on_error=1'}
    for name, sources in cases:
        binary = out / name
        flags = common + (['-DFPGA_MODEL_PROFILE=' + name.rsplit('-', 1)[1]]
                          if name.startswith(('causal-profile-', 'observer-equivalence-')) else [])
        if name == 'c21-compatibility' and uio_sources:
            flags += uio_flags
            sources = [*sources, *uio_sources]
        with (out / (name + '.log')).open('w') as log:
            subprocess.run([args.cc, *flags, *[str(ROOT / n) for n in sources], '-o', str(binary)],
                           stdout=log, stderr=subprocess.STDOUT, check=True)
            subprocess.run([str(binary)], stdout=log, stderr=subprocess.STDOUT, check=True, env=env)
        results.append(name)
        print(name, 'PASS', flush=True)
    subprocess.run([sys.executable, '-m', 'unittest', 'discover', '-s', 'tests', '-p', 'test_c20_tools.py', '-v'],
                   cwd=ROOT, check=True)
    (out / 'result.json').write_text(json.dumps({'passed': True, 'cases': results,
        'hardware_connected': False, 'pre_observation_executor_sha256': baseline_sha, 'uio_reference': uio_reference, 'sanitizers': ['address', 'undefined']}, indent=2) + '\n')

if __name__ == '__main__':
    main()
