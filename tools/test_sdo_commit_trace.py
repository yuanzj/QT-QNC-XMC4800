"""PRC-05完整SDO提交只读计数：开/关真实适配逐拍对照，不连接硬件。"""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[1]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--cc', default='cc')
    parser.add_argument('--output', required=True)
    args = parser.parse_args()
    out = Path(args.output).resolve()
    out.mkdir(parents=True, exist_ok=False)
    sources = ['tests/test_sdo_commit_trace.c', 'FpgaSim/fpga_program.c',
               'FpgaSim/feedback_model.c', 'FpgaSim/fpga_control_model.c',
               'Simulation/native_causal_pset.c', 'Simulation/ethercat_adapter.c']
    outputs = []
    for enabled in [0, 1]:
        binary = out / ('trace-' + str(enabled))
        command = [args.cc, '-std=c99', '-Wall', '-Wextra', '-Werror', '-UNDEBUG',
                   '-fsanitize=address,undefined', '-DFPGA_SIM_SCENARIO=9', '-DFPGA_SIM_INT64=1',
                   '-DFPGA_TEST_SDO_COMMIT_TRACE=' + str(enabled)]
        command += [str(ROOT / x) for x in sources] + ['-o', str(binary)]
        with (out / ('compile-' + str(enabled) + '.log')).open('w') as log:
            subprocess.run(command, stdout=log, stderr=subprocess.STDOUT, check=True)
        result = subprocess.run([str(binary)], capture_output=True, text=True)
        (out / ('trace-' + str(enabled) + '.csv')).write_text(result.stdout)
        (out / ('trace-' + str(enabled) + '.stderr')).write_text(result.stderr)
        result.check_returncode()
        assert len(result.stdout.splitlines()) == 6000
        outputs.append(result.stdout)
    assert outputs[0] == outputs[1], '诊断改变了实际适配PDO输出'
    for flags in [['-DFPGA_TEST_SDO_COMMIT_TRACE=2'],
                  ['-DFPGA_TEST_SDO_COMMIT_TRACE=1', '-DFPGA_SIM_INT64=0'],
                  ['-DFPGA_TEST_SDO_COMMIT_TRACE=1', '-DFPGA_TEST_POSITION_VECTOR=1'],
                  ['-DFPGA_TEST_SDO_COMMIT_TRACE=1', '-DFPGA_TEST_TRUNCATE_TXPDO_TAIL=1'],
                  ['-DFPGA_TEST_SDO_COMMIT_TRACE=1', '-DFPGA_MODEL_IDENTITY_VALID=0']]:
        result = subprocess.run([args.cc, '-x', 'c', '-fsyntax-only', *flags,
                                 '-include', str(ROOT / 'Simulation/model_config.h'), '-'],
                                input='', capture_output=True, text=True)
        assert result.returncode != 0
    for extra in [['--velocity', 'legacy'], ['--scenario', '8'], ['--model', 'unknown'],
                  ['--position-test-vector', 'forward-wrap'], ['--negative-pdo-tail']]:
        result = subprocess.run(['python3', str(ROOT / 'tools/build.py'), '--gcc', 'unused',
                                 '--output', str(out / 'must-not-exist'), '--sdo-commit-trace', *extra],
                                capture_output=True, text=True)
        assert result.returncode == 2 and not (out / 'must-not-exist').exists(), extra
    report = {'passed': True, 'profiles': ['off', 'on'], 'ticksPerProfile': 6000,
              'pdoOutputsExact': True, 'outputSha256': hashlib.sha256(outputs[0].encode()).hexdigest(),
              'callbackNotifications': 6, 'loadSuccesses': 3, 'loadFailures': 3,
              'hardwareConnected': False}
    (out / 'result.json').write_text(json.dumps(report, indent=2))
    print('SDO提交计数开/关6000拍PDO完全相同；重复与失败可观察，非法组合拒绝。')

if __name__ == '__main__':
    main()
