"""配套ESI/SII和Flash保留区检查；仅使用临时文件，不连接探针。"""
import importlib.util
from pathlib import Path
import re
import struct
import tempfile
import unittest
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[1]

def module(name):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'tools' / (name + '.py'))
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result

profile = module('c20_profile')
flash = module('flash')

class C20Tools(unittest.TestCase):
    def test_generated_esi_and_sii_match_current_uio(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            for name in ['SSC/QiaoTian_XMC_Servo_0927.xml', 'SSC/Src/eeprom.h']:
                target = project / name
                target.parent.mkdir(parents=True, exist_ok=True)
                target.write_bytes((ROOT / name).read_bytes())
            profile.apply_profile6(project)
            profile.apply_qiaotian(project)
            tree = ET.parse(project / 'SSC/QiaoTian_XMC_Servo_0927.xml')
            for tag, index, expected, length in [
                ('RxPdo', 0x1600, [0x60400010,0x607A0020,0x60FF0020,0x60710010,0x60600008,0x20010020],17),
                ('TxPdo', 0x1A00, [0x60410010,0x603F0010,0x60640020,0x606C0020,0x60770010,
                    0x2F000120,0x2F000220,0x2F000320,0x2F000440,0x2F000510,0x2F000608,0x2F000708,0x2F000820,0x2F000920],46)]:
                pdo = next(x for x in tree.findall('.//' + tag) if int(x.findtext('Index').replace('#x',''),16)==index)
                entries = [int(e.findtext('Index').replace('#x',''),16)<<16 | int(e.findtext('SubIndex'))<<8 |
                           int(e.findtext('BitLen')) for e in pdo.findall('Entry')]
                self.assertEqual(entries, expected)
                self.assertEqual(sum(e & 255 for e in entries), length * 8)
                # Verify the compiled dictionary initializer, not just the ESI generator.
                objects=(ROOT/'SSC/Src/QiaoTian_XMC_ServoObjects.h').read_text()
                count=6 if index==0x1600 else 14
                match=re.search(r'=\{'+str(count)+r',('+f'0x{expected[0]:08X}'+r'[^}]+)\}',objects)
                self.assertIsNotNone(match)
                declared=[int(n.strip(),16) for n in match[1].split(',')]
                self.assertEqual(declared,expected)
            dictionary = {int(o.findtext('Index').replace('#x',''),16):o for o in tree.findall('.//Dictionary/Objects/Object')}
            self.assertTrue(set([0x2300,0x2310,0x2400,0x2410,0x2420,0x2430,0x2440,0x2500,0x2F00,0x2F10]) <= dictionary.keys())
            self.assertNotIn(0x2100,dictionary)
            raw = bytes(int(x,16) for x in re.findall(r'0x([0-9a-fA-F]{2})',(project/'SSC/Src/eeprom.h').read_text()))
            self.assertEqual(len(raw),2048)
            self.assertEqual(struct.unpack_from('<I',raw,24)[0],0x060B0901)
            offset = 128
            sm = None
            while offset + 4 <= len(raw):
                kind,words=struct.unpack_from('<HH',raw,offset)
                if kind==0xFFFF:break
                if kind==0x29:sm=raw[offset+4:offset+4+words*2]
                offset+=4+words*2
            self.assertIsNotNone(sm)
            self.assertEqual(struct.unpack_from('<H',sm,18)[0],17)
            self.assertEqual(struct.unpack_from('<H',sm,26)[0],46)

    def test_nvm_and_sii_rejected_as_firmware(self):
        for offset in [0x4000,0x8000,0xBFFF,0xC000,0x10000,0x1FFFF]:
            with self.assertRaises(ValueError):
                flash.validate_image({flash.BASE:1,flash.BASE+offset:2},True)
        flash.validate_image({flash.BASE:1,flash.BASE+0x3FFF:2,flash.BASE+0x20000:3},True)
        flash.validate_image({flash.BASE:1,flash.BASE+0x4000:2},False)

    def test_physical_sector_rebuild_preserves_existing_nvm(self):
        before=bytearray((i*31+7)%256 for i in range(0x200000))
        expected=bytearray(before)
        expected[:4]=b'BOOT'
        expected[0x20000:0x20004]=b'CODE'
        with tempfile.TemporaryDirectory() as directory:
            path=Path(directory)/'preserved.hex'
            flash.write_preserved_hex(path,expected)
            rebuilt=flash.read_hex(path)
        for offset in range(0x4000,0xC000):
            self.assertEqual(rebuilt[flash.BASE+offset],before[offset])
        self.assertFalse(any(flash.BASE+0x10000<=p<flash.BASE+0x20000 for p in rebuilt))

if __name__ == '__main__':
    unittest.main()
