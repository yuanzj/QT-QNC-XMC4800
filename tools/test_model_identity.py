"""编译真实型号SDO回调/描述符和模拟/未知两种初始化；不连接硬件。"""
import argparse
from pathlib import Path
import re
import subprocess

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--cc',default='clang');p.add_argument('--output',required=True);a=p.parse_args()
    root=Path(__file__).resolve().parents[1];out=Path(a.output).resolve();out.mkdir(parents=True,exist_ok=False)
    src=(root/'SSC/Src/QiaoTian_XMC_Servo.c').read_text();start=src.index('UINT8 ECAT_Read_0x2214_Callback(');end=src.index('\n}',start)+2
    body=src[start:end];od=(root/'SSC/Src/QiaoTian_XMC_ServoObjects.h').read_text()
    assert 'PROTO UINT8 Tool_model_identity0x2214[SIMULATION_MODEL_IDENTITY_BYTES]' in od
    assert '=SIMULATION_MODEL_IDENTITY_INITIALIZER' in od
    descriptor=re.search(r'OBJCONST TSDOINFOENTRYDESC[^\n]*sEntryDesc0x2214 = [^\n]+',od).group()
    defines=''
    for header,names in [('objdef.h',['DEFTYPE_OCTETSTRING']),('sdoserv.h',['ABORTIDX_UNSUPPORTED_ACCESS','ABORTIDX_PARAM_LENGTH_ERROR'])]:
        text=(root/'SSC/Src'/header).read_text()
        for name in names:defines+=re.search(r'^#define\s+'+name+r'\s+\S+',text,re.M).group()+'\n'
    prefix=r'''#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "Simulation/model_identity.h"
#define UINT8 uint8_t
#define UINT16 uint16_t
#define UINT32 uint32_t
#define OBJCONST const
#define OBJMEM
#define MBXMEM
#define ACCESS_READ 1
struct Desc {uint16_t type,bits,access;};
#define TSDOINFOENTRYDESC struct Desc
static UINT8 Tool_model_identity0x2214[24]=SIMULATION_MODEL_IDENTITY_INITIALIZER;
'''
    suffix=r'''int main(void){
    struct Guard {uint16_t data[12];uint8_t tail[16];} b;unsigned i;
    assert(sEntryDesc0x2214.bits==192&&sEntryDesc0x2214.type==10);
    memset(&b,0xA5,sizeof(b));assert(ECAT_Read_0x2214_Callback(0x2214,0,24,b.data,0)==0);
#if FPGA_MODEL_IDENTITY_VALID
    {const uint8_t literal[24]={'S','I','M','-','Q','N','C','3','0',0,0,0,0,0,0,0,0,0,0,0,0,1,3,0};
     assert(memcmp(b.data,literal,24)==0);assert(FPGA_MODEL_SPEC_CODE==0);}
#else
    for(i=0;i<24;i++)assert(((uint8_t*)b.data)[i]==0);
#endif
    for(i=0;i<16;i++)assert(b.tail[i]==0xA5);
    memset(b.data,0xA5,sizeof(b.data));
    assert(ECAT_Read_0x2214_Callback(0x2214,0,23,b.data,0)==ABORTIDX_PARAM_LENGTH_ERROR);
    assert(ECAT_Read_0x2214_Callback(0x2214,0,25,b.data,0)==ABORTIDX_PARAM_LENGTH_ERROR);
    assert(ECAT_Read_0x2214_Callback(0x2214,1,24,b.data,0)==ABORTIDX_UNSUPPORTED_ACCESS);
    assert(ECAT_Read_0x2214_Callback(0x2214,0,24,b.data,1)==ABORTIDX_UNSUPPORTED_ACCESS);
    for(i=0;i<24;i++)assert(((uint8_t*)b.data)[i]==0xA5);
    return 0;
}'''
    unit=out/'actual-model-sdo.c';unit.write_text(prefix+defines+descriptor+'\n'+body+suffix)
    for valid in [0,1]:
        binary=out/('model-'+str(valid))
        with (out/('model-'+str(valid)+'.log')).open('w') as log:
            subprocess.run([a.cc,'-std=c99','-Wall','-Wextra','-Werror','-UNDEBUG','-fsanitize=address,undefined','-DFPGA_SIM_SCENARIO=9','-DFPGA_SIM_INT64=1','-DFPGA_MODEL_IDENTITY_VALID='+str(valid),'-I'+str(root),str(unit),'-o',str(binary)],stdout=log,stderr=subprocess.STDOUT,check=True)
            subprocess.run([str(binary)],stdout=log,stderr=subprocess.STDOUT,check=True)
        print('型号实际SDO 模拟/未知=',valid,'PASS')
if __name__=='__main__':main()
