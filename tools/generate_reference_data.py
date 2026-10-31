"""导出有来源标签的独立合成接头数据；不得当客户实测曲线或ISO精度认证。"""
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
    cases={'hard':['normal','fast','accel','angle','or','and','safety-torque','safety-angle','window-nok','stop','continue','fail-stop','delay','rundown','release'],'soft':['normal'],'free-run':['normal'],'jam':['normal']}
    expected_nok={'fast','safety-torque','safety-angle','window-nok','stop','continue','fail-stop'}
    results=[]
    for profile,(joint,names) in enumerate(cases.items(),1):
        binary=out/('export-'+joint)
        cmd=[a.cc,'-std=c99','-Wall','-Wextra','-Werror','-UNDEBUG','-fsanitize=address,undefined','-DFPGA_SIM_SCENARIO=9','-DFPGA_MODEL_PROFILE='+str(profile),*[str(ROOT/x) for x in sources],'-o',str(binary)]
        subprocess.run(cmd,check=True)
        for name in names:
            folder=out/(joint+'-'+name);folder.mkdir();csv_path=folder/'trace.csv';wire=folder/'input.bin'
            with csv_path.open('w') as f:subprocess.run([str(binary),name,str(wire)],stdout=f,check=True)
            with csv_path.open() as f:rows=list(csv.DictReader(f))
            final=next(row for row in rows if int(row['state'])!=2)
            expected=0 if name in expected_nok or joint in ('free-run','jam') else 1
            assert int(final['result'])==expected,(joint,name,final)
            meta={'synthetic':True,'calibrated_to_customer_tool':False,'joint':joint,'scenario':9,'case':name,'expected_result':expected,'observed_terminal':final,'scope':'independent synthetic joint + functional reference controller; not physical acceptance','input_sha256':hashlib.sha256(wire.read_bytes()).hexdigest(),'trace_sha256':hashlib.sha256(csv_path.read_bytes()).hexdigest(),'source_sha256':{x:hashlib.sha256((ROOT/x).read_bytes()).hexdigest() for x in sources+['FpgaSim/fpga_program.h','FpgaSim/feedback_model.h','Simulation/native_pset.h','Simulation/model_config.h']},'fixture_constants':{'seat_angle_cdeg':36000,'drag_mnm':200,'stiffness_mnm_per_deg':10 if joint=='soft' else 1000,'capacity_mnm':30000,'brake_rpm_milli_per_ms':2000,'jam_angle_cdeg':500 if joint=='jam' else None,'free_run':joint=='free-run'},'coefficient_origin':'工程明确选择的合成夹具常量；不是厂商标定值；行业资料仅为分阶段与过冲方向依据'}
            (folder/'provenance.json').write_text(json.dumps(meta,ensure_ascii=False,indent=2));results.append(meta)
    (out/'index.json').write_text(json.dumps(results,ensure_ascii=False,indent=2));print('已生成',len(results),'组合成工况，所有结果与预先声明的OK/NOK相符。')
if __name__=='__main__':main()
