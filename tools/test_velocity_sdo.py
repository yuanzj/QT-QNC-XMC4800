# 宿主编译真实SDO回调及实际描述符；验证符号、长度、原子快照及606C越界拒读。
import argparse
from pathlib import Path
import re
import subprocess

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--cc',default='clang');p.add_argument('--output',required=True);a=p.parse_args()
    root=Path(__file__).resolve().parents[1];out=Path(a.output).resolve();out.mkdir(parents=True,exist_ok=False)
    src=(root/'SSC/Src/QiaoTian_XMC_Servo.c').read_text()
    begin=src.index('UINT8 ECAT_Read_0x2212_Callback(');end=src.index('\n#endif',begin)
    body=src[begin:end]
    od=(root/'SSC/Src/QiaoTian_XMC_ServoObjects.h').read_text()
    descriptors='\n'.join(re.search(r'OBJCONST TSDOINFOENTRYDESC[^\n]*sEntryDesc0x'+index+r' = [^\n]+',od).group() for index in ['2212','2213','606C'])
    defines=''
    for header,names in [('objdef.h',['DEFTYPE_INTEGER64','DEFTYPE_INTEGER32','DEFTYPE_UNSIGNED8']),('sdoserv.h',['ABORTIDX_UNSUPPORTED_ACCESS','ABORTIDX_PARAM_LENGTH_ERROR','ABORTIDX_IN_THIS_STATE_DATA_CANNOT_BE_READ_OR_STORED'])]:
        text=(root/'SSC/Src'/header).read_text()
        for name in names:defines+=re.search(r'^#define\s+'+name+r'\s+\S+',text,re.M).group()+'\n'
    prefix=r'''#include <assert.h>
#include <stdint.h>
#include <string.h>
#define OBJCONST const
#define OBJMEM
#define MBXMEM
#define ACCESS_READ 1
#define OBJACCESS_TXPDOMAPPING 2
#define UINT8 uint8_t
#define UINT16 uint16_t
#define UINT32 uint32_t
#define UINT64 uint64_t
struct Desc {uint16_t type,bits,access;};
#define TSDOINFOENTRYDESC struct Desc
static int64_t Velocity_actual_64_0x2212;
static int32_t Velocity_actual_value0x606C;
static uint8_t Velocity_606C_valid0x2213;
static uint32_t irq_mask;
static uint32_t __get_PRIMASK(void){return irq_mask;}
static void __disable_irq(void){irq_mask=1;}
static void __set_PRIMASK(uint32_t mask){irq_mask=mask;}
'''
    suffix=r'''int main(void){
    struct Guard {uint16_t data[4];uint8_t tail[8];} b;
    const uint8_t plus[8]={0,0,0,0xFA,0,0,0,0},minus[8]={0,0,0,6,0xFF,0xFF,0xFF,0xFF};unsigned i;
    assert(sEntryDesc0x2212.type==0x15&&sEntryDesc0x2212.bits==64);
    assert(sEntryDesc0x606C.type==4&&sEntryDesc0x606C.bits==32);
    assert(sEntryDesc0x2213.bits==8);
    memset(&b,0xA5,sizeof(b));Velocity_actual_64_0x2212=4194304000LL;
    assert(ECAT_Read_0x2212_Callback(0x2212,0,8,b.data,0)==0&&irq_mask==0);
    assert(!memcmp(b.data,plus,8));Velocity_actual_64_0x2212=-4194304000LL;irq_mask=1;
    assert(ECAT_Read_0x2212_Callback(0x2212,0,8,b.data,0)==0&&irq_mask==1);
    assert(!memcmp(b.data,minus,8));
    assert(ECAT_Read_0x2212_Callback(0x2212,0,4,b.data,0)==ABORTIDX_PARAM_LENGTH_ERROR);
    assert(ECAT_Read_0x2212_Callback(0x2212,1,8,b.data,0)==ABORTIDX_UNSUPPORTED_ACCESS);
    assert(ECAT_Read_0x2212_Callback(0x2212,0,8,b.data,1)==ABORTIDX_UNSUPPORTED_ACCESS);
    memset(b.data,0xA5,sizeof(b.data));Velocity_606C_valid0x2213=0;Velocity_actual_value0x606C=2097152000;
    assert(ECAT_Read_0x606C_Callback(0x606C,0,4,b.data,0)==0x1A&&irq_mask==1);
    for(i=0;i<8;i++)assert(((uint8_t*)b.data)[i]==0xA5); /* 拒绝时不泄漏最后有效值 */
    Velocity_606C_valid0x2213=1;assert(ECAT_Read_0x606C_Callback(0x606C,0,4,b.data,0)==0);
    assert(((uint8_t*)b.data)[3]==0x7D);
    assert(ECAT_Read_0x606C_Callback(0x606C,0,8,b.data,0)==ABORTIDX_PARAM_LENGTH_ERROR);
    assert(ECAT_Read_0x606C_Callback(0x606C,1,4,b.data,0)==ABORTIDX_UNSUPPORTED_ACCESS);
    assert(ECAT_Read_0x606C_Callback(0x606C,0,4,b.data,1)==ABORTIDX_UNSUPPORTED_ACCESS);
    for(i=0;i<8;i++)assert(b.tail[i]==0xA5);
    return 0;
}'''
    unit=out/'actual-sdo.c';unit.write_text(prefix+defines+descriptors+'\n'+body+suffix)
    binary=out/'actual-sdo'
    with (out/'test.log').open('w') as log:
        subprocess.run([a.cc,'-std=c99','-Wall','-Wextra','-Werror','-UNDEBUG','-fsanitize=address,undefined',str(unit),'-o',str(binary)],stdout=log,stderr=subprocess.STDOUT,check=True)
        subprocess.run([str(binary)],stdout=log,stderr=subprocess.STDOUT,check=True)
    print('真实INT64/606C SDO回调、描述符、长度与越界拒读 PASS')
if __name__=='__main__':main()
