"""编译实际对象类型、SDO字段映射和回调；检查字节值及写入不破坏相邻字段。"""
import argparse
from pathlib import Path
import re
import subprocess

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--cc', default='clang')
    parser.add_argument('--output', required=True)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    out = Path(args.output).resolve()
    out.mkdir(parents=True, exist_ok=False)
    source = (root / 'SSC/Src/QiaoTian_XMC_Servo.c').read_text()
    objects = (root / 'SSC/Src/QiaoTian_XMC_ServoObjects.h').read_text()
    prefix = '''#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "Simulation/model_config.h"
#define UINT8 uint8_t
#define UINT16 uint16_t
#define UINT32 uint32_t
#define INT32 int32_t
#define OBJ_STRUCT_PACKED_START
#define OBJ_STRUCT_PACKED_END
#define MBXMEM
'''
    header = (root / 'SSC/Src/sdoserv.h').read_text()
    for name in ['ABORTIDX_SUBINDEX_NOT_EXISTING', 'ABORTIDX_PARAM_LENGTH_ERROR',
                 'ABORTIDX_READ_ONLY_ENTRY', 'ABORTIDX_UNSUPPORTED_ACCESS']:
        prefix += re.search(r'^#define\s+' + name + r'\s+\S+', header, re.M).group() + '\n'
    checks = []
    for index in ['2000', '2010', '2021', '2022', '2023']:
        end = objects.index('TOBJ' + index + ';') + len('TOBJ' + index + ';')
        start = objects.rfind('typedef struct OBJ_STRUCT_PACKED_START', 0, end)
        declaration = objects[start:end]
        prefix += declaration + '\n'
        variable = re.search(r'PROTO TOBJ' + index + r' (\w+)', objects).group(1)
        prefix += 'static TOBJ' + index + ' ' + variable + ';\n'
        fields = re.findall(r'(UINT8|UINT32|INT32)\s+(\w+)(\[16\])?;', declaration)
        for sub, (kind, field, array) in enumerate(fields, 1):
            if array:
                literal = '"SN-0123456789ABC"'
                checks.append(f'memcpy({variable}.{field},{literal},16);')
            else:
                literal = '0x5A' if kind == 'UINT8' else '0x12345678'
                checks.append(f'{variable}.{field}={literal};')
            size = 16 if array else 1 if kind == 'UINT8' else 4
            checks += [
                'memset(data,0xA5,sizeof(data));',
                f'assert(ECAT_Read_0x{index}_Callback(0x{index},{sub},{size},data,0)==0);',
                f'assert(memcmp(data,&{variable}.{field},{size})==0);',
                f'assert(((uint8_t*)data)[{max(2,size)}]==0xA5);',
                f'assert(ECAT_Read_0x{index}_Callback(0x{index},{sub},{size+1},data,0)==ABORTIDX_PARAM_LENGTH_ERROR);',
            ]
            if index != '2000':
                checks += [
                    f'{{ TOBJ{index} expected; memcpy(&expected,&{variable},sizeof(expected));',
                    f'memset(&expected.{field},0x3C,{size}); memset(data,0x3C,sizeof(data));',
                    f'assert(ECAT_Write_0x{index}_Callback(0x{index},{sub},{size},data,0)==0);',
                    f'assert(memcmp(&expected,&{variable},sizeof(expected))==0); }}',
                ]
            else:
                checks.append(f'assert(ECAT_Write_0x{index}_Callback(0x{index},{sub},{size},data,0)==ABORTIDX_READ_ONLY_ENTRY);')
    body = source[source.index('typedef struct\n{\n    UINT8  size;'):source.index('/* C12 §5.4:')]
    # 规格口径单独按协议字面值校验，不从映射表反推期望。
    checks += ['Tool_Spec0x2000.max_torque=30000;',
               'assert(ECAT_Read_0x2000_Callback(0x2000,3,4,data,0)==0);',
               'assert(data[0]==0x7530 && data[1]==0);',
               'Tool_Spec0x2000.max_speed=500000;',
               'assert(ECAT_Read_0x2000_Callback(0x2000,4,4,data,0)==0);',
               'assert(data[0]==0xA120 && data[1]==7);']
    unit = out / 'actual-fields.c'
    unit.write_text(prefix + body + '\nint main(void){uint16_t data[16];\n' + '\n'.join(checks) + '\nreturn 0;}\n')
    binary = out / 'actual-fields'
    with (out / 'test.log').open('w') as log:
        subprocess.run([args.cc, '-std=c99', '-Wall', '-Wextra', '-Werror', '-UNDEBUG',
                        '-fsanitize=address,undefined', '-I'+str(root), str(unit), '-o', str(binary)],
                       stdout=log, stderr=subprocess.STDOUT, check=True)
        subprocess.run([str(binary)], stdout=log, stderr=subprocess.STDOUT, check=True)
    print('五个实际SDO对象的54字段读写、相邻内存保全及规格字节 PASS')

if __name__ == '__main__':
    main()
