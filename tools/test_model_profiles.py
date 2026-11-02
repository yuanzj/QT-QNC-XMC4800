"""宿主验证逻辑模型、真实PDO拷贝边界与刷写保全算法；不连接或刷写设备。"""
import argparse
import json
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--cc', default='cc', help='支持ASan/UBSan的宿主C编译器，例如clang')
    parser.add_argument('--output', required=True)
    args = parser.parse_args()
    out = Path(args.output).resolve()
    out.mkdir(parents=True, exist_ok=False)
    program = ['FpgaSim/fpga_program.c', 'Simulation/native_pset.c']
    adapter = program + ['Simulation/ethercat_adapter.c']
    cases = [('legacy-wait', 0, 'tests/test_fpga_sim.c', ['FpgaSim/fpga_sim.c'])]
    cases += [('program-' + str(n), n, 'tests/test_fpga_program.c', program) for n in range(5)]
    cases += [('adapter', 0, 'tests/test_ethercat_adapter.c', adapter)]
    cases += [('fault-timing-' + str(n), n, 'tests/test_fault_timing.c', adapter) for n in [0, 4, 6]]
    cases += [('position-vector', 5, 'tests/test_position_vector.c', ['FpgaSim/fpga_program.c'])]
    cases += [('raw-integer-vector', 8, 'tests/test_raw_integer_vector.c', ['FpgaSim/fpga_program.c'])]
    results = []
    for label, scenario, test, sources in cases:
        binary = out / label
        command = [args.cc, '-std=c99', '-Wall', '-Wextra', '-Werror', '-UNDEBUG',
                   '-fsanitize=address,undefined', '-DFPGA_SIM_SCENARIO=' + str(scenario),
                   '-I' + str(ROOT), str(ROOT / test)]
        command += [str(ROOT / source) for source in sources]
        command += ['-o', str(binary)]
        with (out / (label + '.log')).open('w') as log:
            subprocess.run(command, stdout=log, stderr=subprocess.STDOUT, check=True)
            subprocess.run([str(binary)], stdout=log, stderr=subprocess.STDOUT, check=True)
        results.append({'case': label, 'scenario': scenario, 'passed': True})
        print(label, 'PASS', flush=True)
    causal = ['tests/test_causal_model.c', 'FpgaSim/fpga_program.c', 'FpgaSim/feedback_model.c',
              'FpgaSim/fpga_control_model.c', 'Simulation/native_causal_pset.c']
    for mode, profile in [(m,p) for m in [0,1] for p in [1,2,3,4]]:
        label = 'causal-profile-' + str(profile) + '-int64-' + str(mode)
        binary = out / label
        command = [args.cc, '-std=c99', '-Wall', '-Wextra', '-Werror', '-UNDEBUG',
                   '-fsanitize=address,undefined', '-DFPGA_SIM_SCENARIO=9', '-DFPGA_SIM_INT64='+str(mode), '-DFPGA_MODEL_PROFILE=' + str(profile)]
        command += [str(ROOT / source) for source in causal] + ['-o', str(binary)]
        with (out / (label + '.log')).open('w') as log:
            subprocess.run(command, stdout=log, stderr=subprocess.STDOUT, check=True)
            subprocess.run([str(binary)], stdout=log, stderr=subprocess.STDOUT, check=True)
        results.append({'case': label, 'scenario': 9, 'joint_profile': profile, 'int64': mode, 'passed': True})
        print(label, 'PASS', flush=True)
    for mode, profile in [(0,3),(1,3),(1,1)]:
        label = 'velocity64-mode-' + str(mode) + '-profile-' + str(profile)
        binary = out / label
        sources = ['tests/test_velocity64.c', *causal[1:], 'Simulation/ethercat_adapter.c']
        command = [args.cc, '-std=c99', '-Wall', '-Wextra', '-Werror', '-UNDEBUG',
                   '-fsanitize=address,undefined', '-DFPGA_SIM_SCENARIO=9', '-DFPGA_SIM_INT64='+str(mode), '-DFPGA_MODEL_PROFILE='+str(profile)]
        command += [str(ROOT / source) for source in sources] + ['-o', str(binary)]
        with (out / (label+'.log')).open('w') as log:
            subprocess.run(command, stdout=log, stderr=subprocess.STDOUT, check=True)
            subprocess.run([str(binary)], stdout=log, stderr=subprocess.STDOUT, check=True)
        results.append({'case': label, 'scenario': 9, 'joint_profile': profile, 'int64': mode, 'passed': True})
        print(label, 'PASS', flush=True)
    with (out / 'actual-mapping.log').open('w') as log:
        subprocess.run([sys.executable, str(ROOT / 'tools/test_mapping_profile.py'),
                        '--cc', args.cc, '--output', str(out / 'mapping')],
                       stdout=log, stderr=subprocess.STDOUT, check=True)
    with (out / 'actual-sdo.log').open('w') as log:
        subprocess.run([sys.executable, str(ROOT / 'tools/test_velocity_sdo.py'), '--cc', args.cc,
                        '--output', str(out / 'sdo')], stdout=log, stderr=subprocess.STDOUT, check=True)
    with (out / 'model-identity.log').open('w') as log:
        subprocess.run([sys.executable, str(ROOT / 'tools/test_model_identity.py'), '--cc', args.cc,
                        '--output', str(out / 'model-identity')], stdout=log, stderr=subprocess.STDOUT, check=True)
    with (out / 'flash-boundaries.log').open('w') as log:
        subprocess.run([sys.executable, '-m', 'unittest', 'discover', '-s', 'tests',
                        '-p', 'test_flash_tools.py', '-v'], cwd=ROOT,
                       stdout=log, stderr=subprocess.STDOUT, check=True)
    report = {'passed': True, 'c_model_runs': results, 'actual_mapping_profiles': ['0-legacy','7-legacy-negative','9-legacy','9-int64'],
              'velocity_sdo_callback_test': True, 'model_identity_sdo_profiles': ['unknown','simulation'], 'flash_boundary_tests': 3, 'assertions': '-UNDEBUG',
              'sanitizers': ['address', 'undefined'], 'hardware_connected': False}
    (out / 'result.json').write_text(json.dumps(report, ensure_ascii=False, indent=2))
    print('23个C运行、4个实际映射配置、实际SDO回调、3项刷写边界测试通过；不代表实物测试。')

if __name__ == '__main__':
    main()
