"""Compile actual PDO copy code and mapping initializer for normal/negative profiles.
No probe, NIC, firmware flashing or physical timing claims.
"""
import argparse
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
    prefix=r'''#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "Simulation/test_mapping.h"
typedef uint8_t UINT8;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
static uint32_t status_code0x2200=0x12345678, status_code20x2201;
static int16_t Torque_actual_value0x6077;
static uint16_t Statusword0x6041, pset_echo0x220B;
static int32_t Position_actual_value0x6064, Velocity_actual_value0x606C, current_sample0x2208;
static uint8_t step_echo0x220C,step_result0x220D;
struct Mapping {uint16_t count;uint32_t entries[13];};
'''
    suffix=r'''int main(void) {
    struct Guard {uint8_t bytes[SIMULATION_TX_PDO_BYTES];uint8_t sentinel[16];} data;
    unsigned bits=0,i;
    memset(&data,0xA5,sizeof(data));
    for(i=0;i<mapping.count;++i) bits+=mapping.entries[i]&255U;
    assert(bits/8==SIMULATION_TX_PDO_BYTES && bits%8==0);
    APPL_InputMapping((UINT16*)data.bytes);
    assert(data.bytes[0]==0x78 && data.bytes[1]==0x56 && data.bytes[2]==0x34 && data.bytes[3]==0x12);
    for(i=0;i<sizeof(data.sentinel);++i) assert(data.sentinel[i]==0xA5);
    return 0;
}
'''
    unit=out/'actual-mapping.c';unit.write_text(prefix+'static const struct Mapping mapping='+initializer+';\n'+body+suffix)
    for scenario in [0,7]:
        binary=out/('mapping-'+str(scenario))
        cmd=[args.cc,'-std=c99','-Wall','-Wextra','-Werror','-UNDEBUG','-fsanitize=address,undefined','-DFPGA_SIM_SCENARIO='+str(scenario),'-I'+str(root),str(unit),'-o',str(binary)]
        with (out/('scenario-'+str(scenario)+'.log')).open('w') as log:
            subprocess.run(cmd,stdout=log,stderr=subprocess.STDOUT,check=True)
            subprocess.run([str(binary)],stdout=log,stderr=subprocess.STDOUT,check=True)
        print('Actual mapping and guarded PDO buffer scenario',scenario,'PASS')

if __name__=='__main__':main()
