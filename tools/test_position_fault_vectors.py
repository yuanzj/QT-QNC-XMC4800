"""MAP-04显式位置协议向量：实际适配逐拍与正常模型比较，不连接设备。"""
import argparse
import csv
import json
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[1]

def signed(value):
    return (value + (1 << 31)) % (1 << 32) - (1 << 31)

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--cc', default='cc')
    parser.add_argument('--output', required=True)
    args = parser.parse_args()
    out = Path(args.output).resolve()
    out.mkdir(parents=True, exist_ok=False)
    sources = ['tests/test_position_fault_adapter.c','FpgaSim/fpga_program.c',
               'FpgaSim/feedback_model.c','FpgaSim/fpga_control_model.c',
               'Simulation/native_causal_pset.c','Simulation/ethercat_adapter.c']
    runs = []
    for mode in range(4):
        binary = out / ('vector-' + str(mode))
        command = [args.cc,'-std=c99','-Wall','-Wextra','-Werror','-UNDEBUG',
                   '-fsanitize=address,undefined','-DFPGA_SIM_SCENARIO=9','-DFPGA_SIM_INT64=1',
                   '-DFPGA_TEST_POSITION_VECTOR='+str(mode), *[str(ROOT/x) for x in sources], '-o',str(binary)]
        with (out / ('compile-'+str(mode)+'.log')).open('w') as log:
            subprocess.run(command, stdout=log, stderr=subprocess.STDOUT, check=True)
        result = subprocess.run([str(binary)],capture_output=True,text=True)
        (out/('vector-'+str(mode)+'.csv')).write_text(result.stdout)
        (out/('vector-'+str(mode)+'.stderr')).write_text(result.stderr)
        result.check_returncode()
        runs.append([[int(x) for x in row] for row in csv.reader(result.stdout.splitlines())])
    assert all(len(x)==6000 for x in runs)
    wraps = []
    for mode, rows in enumerate(runs):
        same_step_wraps = []
        for i,(normal,actual) in enumerate(zip(runs[0],rows)):
            assert normal[:-1]==actual[:-1], (mode,i,'non-position output changed')
            n,step = normal[-1],normal[1]
            expected = n if not step or mode==0 else signed((2147483647-262144+n) if mode==1 else (-2147483648+262144-n) if mode==2 else ((2147483647-536870912 if step&1 else -2147483648+536870912)+n))
            assert actual[-1]==expected,(mode,i)
            if i and step and rows[i-1][1]==step and abs(actual[-1]-rows[i-1][-1])>2147483647:
                same_step_wraps.append({'ms':actual[0],'step':step,'from':rows[i-1][-1],'to':actual[-1]})
        assert bool(same_step_wraps)==(mode in [1,2]),(mode,same_step_wraps)
        wraps.append({'mode':mode,'sameStepWraps':same_step_wraps,'nonPositionOutputsExact':True})
    for mode in [-1,4]:
        result = subprocess.run([args.cc,'-x','c','-fsyntax-only','-DFPGA_TEST_POSITION_VECTOR='+str(mode),
                                 '-include',str(ROOT/'Simulation/model_config.h'),'-'],input='',capture_output=True,text=True)
        assert result.returncode!=0
    for extra in [['--velocity','legacy'],['--scenario','8'],['--model','unknown'],['--negative-pdo-tail']]:
        result = subprocess.run(['python3',str(ROOT/'tools/build.py'),'--gcc','unused',
                                 '--output',str(out/'must-not-exist'),'--position-test-vector','forward-wrap',*extra],
                                capture_output=True,text=True)
        assert result.returncode==2 and not (out/'must-not-exist').exists(),extra
    (out/'result.json').write_text(json.dumps({'passed':True,'ticksPerMode':6000,'modes':wraps,'invalidModesRejected':[-1,4]},indent=2))
    print('四种实际适配配置逐拍比较通过；正反回绕存在，正常/跨步对照无同一步回绕；不代表实板。')

if __name__=='__main__': main()
