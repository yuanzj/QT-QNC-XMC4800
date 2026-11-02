"""Compile actual PDO copy code and mapping initializer for normal/negative profiles.
No probe, NIC, firmware flashing or physical timing claims.
"""
import argparse
import json
from pathlib import Path
import re
import subprocess

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--cc',default='cc')
    parser.add_argument('--output',required=True)
    args=parser.parse_args()
    root=Path(__file__).resolve().parents[1]
    out=Path(args.output).resolve();out.mkdir(parents=True,exist_ok=False)
    source=(root/'SSC/Src/QiaoTian_XMC_Servo.c').read_text()
    begin=source.index('void APPL_InputMapping(UINT16* pData)')
    end=source.index('void APPL_InputMapping_New',begin)
    body=source[begin:end]
    objects=(root/'SSC/Src/QiaoTian_XMC_ServoObjects.h').read_text()
    initializer=re.search(r'=\{SIMULATION_TX_PDO_ENTRY_COUNT,[^}]+\}',objects).group()[1:]
    count,entries=initializer[1:-1].split(',',1)
    initializer='{'+count+', {'+entries+'}}'
    profile=json.loads((root/'Simulation/pdo-map4.json').read_text())
    map_asserts='\n'.join('assert(mapping.entries[%d]==%sU);' % (i,e['mapping']) for i,e in enumerate(profile['entries']))
    assert profile['tx_bytes']==44 and sum(e['bytes'] for e in profile['entries'])==44
    tool=re.search(r'=\{12,"QIAOTIAN-TW-0001"[^}]+\}',objects).group()[1:]
    prefix=r'''#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "Simulation/test_mapping.h"
typedef uint8_t UINT8;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;
#if FPGA_SIM_INT64
static int64_t Velocity_actual_64_0x2212;
#endif
static uint32_t status_code0x2200=0x12345678, status_code20x2201;
static int16_t Torque_actual_value0x6077;
static uint16_t Statusword0x6041, pset_echo0x220B;
static int32_t Position_actual_value0x6064, Velocity_actual_value0x606C, current_sample0x2208;
static uint8_t step_echo0x220C,step_result0x220D;
struct Mapping {uint16_t count;uint32_t entries[13];};
struct Tool {uint16_t count;uint8_t sn[16],model;uint32_t max_torque,max_speed;uint8_t max_temp,maintenance;uint32_t service_interval,used_life,max_life,torque_cal,reserved1,reserved2;};
'''
    suffix=r'''int main(void) {
    struct Guard {uint8_t bytes[SIMULATION_TX_PDO_BYTES];uint8_t sentinel[16];} data;
    unsigned bits=0,i;
    assert(tool_spec.max_speed==FPGA_MODEL_MAX_RPM_MILLI);
    memset(&data,0xA5,sizeof(data));
    for(i=0;i<mapping.count;++i) bits+=mapping.entries[i]&255U;
    assert(bits/8==SIMULATION_TX_PDO_BYTES && bits%8==0);
    APPL_InputMapping((UINT16*)data.bytes);
    assert(data.bytes[0]==0x78 && data.bytes[1]==0x56 && data.bytes[2]==0x34 && data.bytes[3]==0x12);
#if FPGA_SIM_INT64
    {
        const int64_t v[]={4194304000LL,-4194304000LL,2097152000LL,-2097152000LL,INT64_MIN,INT64_MAX};
        const uint8_t expected[][8]={{0,0,0,0xFA,0,0,0,0},{0,0,0,6,0xFF,0xFF,0xFF,0xFF},
            {0,0,0,0x7D,0,0,0,0},{0,0,0,0x83,0xFF,0xFF,0xFF,0xFF},
            {0,0,0,0,0,0,0,0x80},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F}};
        unsigned n;
        assert(mapping.entries[5]==0x22120040&&SIMULATION_TX_PDO_BYTES==44);
        /* MAP_ASSERTS */
        for(n=0;n<6;++n){
            Velocity_actual_64_0x2212=v[n];pset_echo0x220B=0x7A03;step_echo0x220C=3;step_result0x220D=1;current_sample0x2208=-2;
            APPL_InputMapping((UINT16*)data.bytes);
            assert(memcmp(data.bytes+16,expected[n],8)==0);
            assert(data.bytes[24]==3&&data.bytes[25]==122&&data.bytes[26]==3&&data.bytes[27]==1);
            assert(data.bytes[28]==0xFE&&data.bytes[29]==0xFF&&data.bytes[30]==0xFF&&data.bytes[31]==0xFF);
            for(i=32;i<44;++i)assert(data.bytes[i]==0);
        }
        (void)Velocity_actual_value0x606C;
    }
#else
    assert(mapping.entries[5]==0x606C0020);
#endif
    for(i=0;i<sizeof(data.sentinel);++i) assert(data.sentinel[i]==0xA5);
    return 0;
}
'''
    suffix=suffix.replace('/* MAP_ASSERTS */',map_asserts)
    unit=out/'actual-mapping.c';unit.write_text(prefix+'static const struct Mapping mapping='+initializer+';\n'+'static const struct Tool tool_spec='+tool+';\n'+body+suffix)
    for scenario,mode in [(0,0),(7,0),(9,0),(9,1)]:
        binary=out/('mapping-'+str(scenario)+'-'+str(mode))
        cmd=[args.cc,'-std=c99','-Wall','-Wextra','-Werror','-UNDEBUG','-fsanitize=address,undefined','-DFPGA_SIM_SCENARIO='+str(scenario),'-DFPGA_SIM_INT64='+str(mode),'-I'+str(root),str(unit),'-o',str(binary)]
        with (out/('scenario-'+str(scenario)+'-'+str(mode)+'.log')).open('w') as log:
            subprocess.run(cmd,stdout=log,stderr=subprocess.STDOUT,check=True)
            subprocess.run([str(binary)],stdout=log,stderr=subprocess.STDOUT,check=True)
        print('Actual mapping and guarded PDO buffer scenario',scenario,'INT64',mode,'PASS')

if __name__=='__main__':main()
