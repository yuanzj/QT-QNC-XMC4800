"""导出INT64边界合成数据，固定输入/夹具，含明确NOK；不连接设备。"""
import argparse
import csv
import hashlib
import json
from pathlib import Path
import subprocess
ROOT=Path(__file__).resolve().parents[1]
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--cc',default='clang');p.add_argument('--output',required=True);a=p.parse_args()
    out=Path(a.output).resolve();out.mkdir(parents=True,exist_ok=False)
    sources=['tools/export_causal_trace.c','FpgaSim/fpga_program.c','FpgaSim/feedback_model.c','FpgaSim/fpga_control_model.c','Simulation/native_causal_pset.c']
    results=[]
    for profile,names in [(3,['speed1000-forward','speed1000-reverse','position1000-overflow']),(1,['speed1000-hard'])]:
        binary=out/('export-'+str(profile))
        subprocess.run([a.cc,'-std=c99','-Wall','-Wextra','-Werror','-UNDEBUG','-fsanitize=address,undefined','-DFPGA_SIM_SCENARIO=9','-DFPGA_SIM_INT64=1','-DFPGA_MODEL_PROFILE='+str(profile),*[str(ROOT/s) for s in sources],'-o',str(binary)],check=True)
        for name in names:
            folder=out/name;folder.mkdir();wire=folder/'input.bin';trace=folder/'trace.csv'
            with trace.open('w') as f:subprocess.run([str(binary),name,str(wire)],stdout=f,check=True)
            with trace.open() as f:rows=list(csv.DictReader(f))
            terminal=next(row for row in rows if int(row['state'])!=2)
            if name in ['speed1000-forward','speed1000-reverse']:
                assert int(terminal['result'])==1 and int(terminal['state'])==3
                sign=-1 if name.endswith('reverse') else 1
                assert int(rows[100]['velocity_inc_s'])==sign*4194304000
                assert int(rows[100]['feedback_rpm_milli'])==sign*1000000
            else:
                expected_fault=0x7002 if name=='position1000-overflow' else 0x7007
                assert int(terminal['result'])==0 and int(terminal['fault_code'])==expected_fault
            meta={'synthetic':True,'physical_calibration':False,'profile':profile,'case':name,'scope':'host model reference only; not board/HMI joint acceptance','terminal':terminal,'input_sha256':hashlib.sha256(wire.read_bytes()).hexdigest(),'trace_sha256':hashlib.sha256(trace.read_bytes()).hexdigest(),'sources':{s:hashlib.sha256((ROOT/s).read_bytes()).hexdigest() for s in sources+['Simulation/model_config.h','Simulation/pdo-map4.json','FpgaSim/fpga_program.h','FpgaSim/feedback_model.h']}}
            (folder/'provenance.json').write_text(json.dumps(meta,ensure_ascii=False,indent=2));results.append(meta)
    (out/'index.json').write_text(json.dumps(results,ensure_ascii=False,indent=2));print('4组INT64合成输入/曲线及来源校验通过')
if __name__=='__main__':main()
