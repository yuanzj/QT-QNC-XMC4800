"""在独立构建快照中生成profile6的ESI/SII。"""
from pathlib import Path
import re
import struct
import xml.etree.ElementTree as ET

MAPPING = [0x22000020, 0x22010020, 0x60770010, 0x60410010, 0x60640020, 0x606c0020,
           0x220b0010, 0x220c0008, 0x220d0008, 0x22080020, 0x00000020, 0x00000020, 0x00000020]
MAPPING[5] = 0x22120040


def update_sii(raw):
    if len(raw) != 2048:
        raise ValueError('SII必须为已锁定的2048B格式')
    result = bytearray(raw[:128]); offset = 128; found = False
    struct.pack_into('<I', result, 24, 0x06000001)
    while offset + 4 <= len(raw):
        kind, words = struct.unpack_from('<HH', raw, offset)
        if kind == 0xffff:
            result += b'\xff\xff\xff\xff'
            break
        data = raw[offset+4:offset+4+words*2]
        if len(data) != words*2:
            raise ValueError('SII分类截断')
        if kind == 0x29:
            data=bytearray(data)
            # SII同步管理器记录各8B，SM3长度更新为44B。
            if len(data)<32: raise ValueError('SII缺少SM3')
            struct.pack_into('<H',data,3*8+2,44)
        if kind == 0x32:
            if len(data) != 112 or struct.unpack_from('<H', data)[0] != 0x1a00 or data[2] != 13:
                raise ValueError('旧TxPDO分类不匹配，拒绝猜测布局')
            data = bytearray(data)
            struct.pack_into('<HBBBBH',data,8+5*8,0x2212,0,0,0x15,64,0)
            found = True
        result += struct.pack('<HH', kind, len(data)//2) + data
        offset += 4 + words*2
    else:
        raise ValueError('SII缺少结束分类')
    if not found or len(result) > 2048:
        raise ValueError('SII分类缺失或超长')
    return bytes(result).ljust(2048, b'\xff')


def apply_profile6(project):
    project = Path(project)
    esi = project / 'SSC/QiaoTian_XMC_Servo_0927.xml'
    tree = ET.parse(esi)
    pdo = next(x for x in tree.findall('.//TxPdo') if int(x.findtext('Index').replace('#x', ''), 16) == 0x1a00)
    entries = pdo.findall('Entry')
    if len(entries) != 13:
        raise ValueError('ESI原映射不是13项')
    for key,text in [('Index','#x2212'),('BitLen','64'),('Name','Velocity_inc_s_64'),('DataType','LINT')]:
        entries[5].find(key).text=text
    for sm in tree.findall('.//Device/Sm'):
        if (sm.text or '').strip()=='Inputs': sm.set('DefaultSize','44')
    for device_type in tree.findall('.//Device/Type'):
        device_type.set('RevisionNo', '#x06000001')
    tree.write(esi, encoding='utf-8', xml_declaration=True)
    header = project / 'SSC/Src/eeprom.h'
    raw = bytes(int(x, 16) for x in re.findall(r'0x([0-9a-fA-F]{2})', header.read_text()))
    new = update_sii(raw)
    header.write_text('/* profile6开发SII，产自锁定输入；现场SII须单独回读验证。 */\nunsigned char aEepromData[] = {\n' +
                      '\n'.join(','.join(f'0x{x:02X}' for x in new[i:i+16])+',' for i in range(0, len(new), 16)) + '\n};\n')


QEC_RX=[0x60400010,0x607A0020,0x60FF0020,0x60710010,0x60600008,0x20010020]
QEC_TX=[0x60410010,0x603F0010,0x60640020,0x606C0020,0x60770010,
        0x2F000120,0x2F000220,0x2F000320,0x2F000440,0x2F000510,
        0x2F000608,0x2F000708,0x2F000820,0x2F000920]

def qec_type(entry):
    """映射类型以对象语义固定。"""
    signed={0x607A0020,0x60FF0020,0x60710010,0x60600008,0x60640020,0x606C0020,
            0x60770010,0x2F000320,0x2F000440,0x2F000820}
    bits=entry&255
    return ({8:'SINT',16:'INT',32:'DINT',64:'LINT'} if entry in signed else
            {8:'USINT',16:'UINT',32:'UDINT',64:'ULINT'})[bits]


def qec_sii(raw):
    """只从已核验profile6转换；现场SII仍须单独备份。"""
    if len(raw)!=2048:raise ValueError('SII长度错误')
    result=bytearray(raw[:128]);struct.pack_into('<I',result,24,0x060B0901)
    offset=128;found=set()
    while offset+4<=len(raw):
        kind,words=struct.unpack_from('<HH',raw,offset)
        if kind==0xffff:result+=b'\xff'*4;break
        data=raw[offset+4:offset+4+words*2]
        if len(data)!=words*2:raise ValueError('SII分类截断')
        if kind==0x29:
            data=bytearray(data)
            if len(data)<32:raise ValueError('SII缺少SM2/3')
            struct.pack_into('<H',data,18,17);struct.pack_into('<H',data,26,46)
        if kind in (0x32,0x33):
            entries=QEC_TX if kind==0x32 else QEC_RX;index=0x1A00 if kind==0x32 else 0x1600
            if len(data)<8 or struct.unpack_from('<H',data)[0]!=index:raise ValueError('SII PDO不匹配')
            head=bytearray(data[:8]);head[2]=len(entries);data=head
            for e in entries:
                bits=e&255;dtype={'SINT':2,'INT':3,'DINT':4,'USINT':5,'UINT':6,'UDINT':7,'LINT':0x15,'ULINT':0x1B}[qec_type(e)]
                data+=struct.pack('<HBBBBH',e>>16,(e>>8)&255,0,dtype,bits,0)
            found.add(kind)
        result+=struct.pack('<HH',kind,len(data)//2)+data;offset+=4+words*2
    else:raise ValueError('SII缺少结束分类')
    if found!={0x32,0x33} or len(result)>2048:raise ValueError('SII缺少PDO或超长')
    return bytes(result).ljust(2048,b'\xff')


def apply_qiaotian(project):
    """生成本项目17/46B配套ESI/SII，基础表与兼容扩展分别标识。"""
    project=Path(project);esi=project/'SSC/QiaoTian_XMC_Servo_0927.xml';tree=ET.parse(esi)
    for tag,entries,index in [('RxPdo',QEC_RX,0x1600),('TxPdo',QEC_TX,0x1A00)]:
        pdo=next(x for x in tree.findall('.//'+tag) if int(x.findtext('Index').replace('#x',''),16)==index)
        for entry in list(pdo.findall('Entry')):pdo.remove(entry)
        for e in entries:
            entry=ET.SubElement(pdo,'Entry');bits=e&255
            for key,value in [('Index',f'#x{e>>16:04X}'),('SubIndex',str((e>>8)&255)),('BitLen',str(bits)),('Name',f'QEC_{e:08X}'),('DataType',qec_type(e))]:
                ET.SubElement(entry,key).text=value
    for sm in tree.findall('.//Device/Sm'):
        if (sm.text or '').strip()=='Inputs':sm.set('DefaultSize','46')
        if (sm.text or '').strip()=='Outputs':sm.set('DefaultSize','17')
    for device in tree.findall('.//Device/Type'):device.set('RevisionNo','#x060B0901')
    qec_dictionary(tree)
    tree.write(esi,encoding='utf-8',xml_declaration=True)
    header=project/'SSC/Src/eeprom.h';raw=bytes(int(x,16) for x in re.findall(r'0x([0-9a-fA-F]{2})',header.read_text()))
    data=qec_sii(raw)
    header.write_text('/* 桥田基础PDO和项目兼容扩展的配套开发SII。 */\nunsigned char aEepromData[] = {\n'+'\n'.join(','.join(f'0x{x:02X}' for x in data[i:i+16])+',' for i in range(0,2048,16))+'\n};\n')


def qec_dictionary(tree):
    """ESI字典同步实际记录宽度/访问。"""
    dictionary=tree.find('.//Dictionary');types=dictionary.find('DataTypes');objects=dictionary.find('Objects')
    for index in (0x2100,0x2300,0x1600,0x1A00):
        for obj in list(objects):
            if obj.findtext('Index','').lower()==f'#x{index:04x}':objects.remove(obj)
    sizes={'USINT':8,'SINT':8,'UINT':16,'INT':16,'UDINT':32,'DINT':32,'LINT':64,'ULINT':64,'STRING(16)':128}
    if not any(t.findtext('Name')=='STRING(16)' for t in types):
        t=ET.SubElement(types,'DataType');ET.SubElement(t,'Name').text='STRING(16)';ET.SubElement(t,'BitSize').text='128'
    definitions={
      0x1600:[(i,'UDINT','ro') for i in range(1,7)],
      0x1A00:[(i,'UDINT','ro') for i in range(1,15)],
      0x2300:[(i,t,'ro') for i,t in enumerate(['STRING(16)','STRING(16)','UINT','UDINT','UDINT','UDINT','UDINT','UDINT','STRING(16)','UDINT','UDINT','UDINT','UINT'],1)],
      0x2310:[(i,t,'rw') for i,t in enumerate(['USINT','UINT','UDINT','DINT','UDINT','USINT'],1)],
      0x2400:[(i,t,'rw') for i,t in enumerate(['UDINT','UINT','USINT','UDINT','UINT','UDINT','USINT','USINT'],1)],
      0x2410:[(i,t,'rw') for i,t in enumerate(['UDINT','UINT','UINT','UINT','USINT','USINT','USINT','USINT','USINT','USINT','USINT','UDINT','UDINT','UDINT','UDINT'],1)],
      0x2420:[(i,t,'rw') for i,t in enumerate(['USINT','UDINT','UINT','USINT','USINT','UINT','UINT','USINT','USINT','USINT','USINT','USINT','USINT','UDINT','UDINT','UDINT','UDINT','UDINT','UDINT','UDINT','UDINT','UDINT','USINT','USINT','USINT'],1)],
      0x2430:[(i,t,'rw') for i,t in enumerate(['UDINT','UINT','UINT','UINT','USINT','UDINT','UDINT','UDINT'],1)],
      0x2500:[(i,'UDINT','ro') for i in (0x10,0x12,0x13,0x15)],
      0x2F00:[(i,qec_type(e),'ro') for i,e in enumerate(QEC_TX[5:],1)],
      0x2F10:[(1,'ULINT','rw')]}
    definitions[0x2440]=definitions[0x2420]
    for index,items in definitions.items():
        name=f'QEC_DT{index:04X}'
        for old in list(types):
            if old.findtext('Name')==name:types.remove(old)
        t=ET.SubElement(types,'DataType');ET.SubElement(t,'Name').text=name;total=ET.SubElement(t,'BitSize');offset=16
        for sub,dtype,access in [(0,'USINT','ro')]+items:
            x=ET.SubElement(t,'SubItem')
            for k,v in [('SubIdx',str(sub)),('Name',f'QEC_{index:04X}_{sub:02X}'),('Type',dtype),('BitSize',str(sizes[dtype])),('BitOffs',str(0 if sub==0 else offset))]:ET.SubElement(x,k).text=v
            f=ET.SubElement(x,'Flags');ET.SubElement(f,'Access').text=access
            if index==0x2F00 and sub:ET.SubElement(f,'PdoMapping').text='t'
            if sub:offset+=sizes[dtype]
        total.text=str(offset)
        obj=ET.SubElement(objects,'Object')
        for k,v in [('Index',f'#x{index:04X}'),('Name',f'QEC_{index:04X}'),('Type',name),('BitSize',str(offset))]:ET.SubElement(obj,k).text=v
        info=ET.SubElement(obj,'Info');head=ET.SubElement(info,'SubItem');ET.SubElement(head,'Name').text=f'QEC_{index:04X}_00'
        default=ET.SubElement(head,'Info');ET.SubElement(default,'DefaultData').text=f'{max(i[0] for i in items):02X}'
        if index in (0x1600,0x1A00):
            for i,e in enumerate(QEC_RX if index==0x1600 else QEC_TX,1):
                x=ET.SubElement(info,'SubItem');ET.SubElement(x,'Name').text=f'QEC_{index:04X}_{i:02X}'
                ET.SubElement(ET.SubElement(x,'Info'),'DefaultData').text=struct.pack('<I',e).hex()
