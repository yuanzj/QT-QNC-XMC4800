"""仅测试HEX校验与扇区保全，不连接设备。"""
import importlib.util
from pathlib import Path
import tempfile
import unittest

spec = importlib.util.spec_from_file_location('flash', Path(__file__).parents[1] / 'tools/flash.py')
flash = importlib.util.module_from_spec(spec)
spec.loader.exec_module(flash)

class FlashBoundaries(unittest.TestCase):
    def test_sector_holes_preserved_and_sii_excluded(self):
        original = bytearray((i * 17 + 3) % 256 for i in range(0x200000))
        original[0:4] = b'BOOT'
        original[0x20000:0x20004] = b'CODE'
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'preserved.hex'
            flash.write_preserved_hex(path, original)
            data = flash.read_hex(path)
        self.assertEqual(len(data), 0x30000)
        self.assertFalse(any(flash.BASE + 0x10000 <= address < flash.BASE + 0x20000 for address in data))
        self.assertTrue(all(byte == original[address - flash.BASE] for address, byte in data.items()))

    def test_checksum_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'bad.hex'
            path.write_text(':020000040C0000\n:00000001FF\n')
            with self.assertRaises(ValueError): flash.read_hex(path)

    def test_sii_write_rejected(self):
        lines = [flash.record(0, 4, b'\x0c\x01'), flash.record(0, 0, b'BAD'), flash.record(0, 1, b'')]
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'sii.hex'
            path.write_text('\n'.join(lines))
            with self.assertRaises(ValueError): flash.read_hex(path)

if __name__ == '__main__': unittest.main()
