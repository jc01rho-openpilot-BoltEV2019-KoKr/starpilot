from openpilot.system.hardware.chestnut import flash as chestnut_flash


def test_usb2_flash_reads_are_limited_to_ep0_packet_size(tmp_path, monkeypatch):
  (tmp_path / "speed").write_text("480\n")
  monkeypatch.setattr(chestnut_flash, "find_chestnut", lambda: (str(tmp_path), ("3801", "0001"), "custom test-CLEAN"))
  monkeypatch.setattr(chestnut_flash, "claim_interface", lambda _: 123)
  flash = chestnut_flash.Flash()

  flash.connect()

  assert flash.max_register_read_size == 64


def test_superspeed_flash_keeps_full_register_reads(tmp_path, monkeypatch):
  (tmp_path / "speed").write_text("5000\n")
  monkeypatch.setattr(chestnut_flash, "find_chestnut", lambda: (str(tmp_path), ("3801", "0001"), "custom test-CLEAN"))
  monkeypatch.setattr(chestnut_flash, "claim_interface", lambda _: 123)
  flash = chestnut_flash.Flash()

  flash.connect()

  assert flash.max_register_read_size == chestnut_flash.MAX_REGISTER_READ_SIZE


def test_flash_read_uses_negotiated_register_chunk_size(monkeypatch):
  flash = chestnut_flash.Flash()
  flash.max_register_read_size = 64
  reads = []
  monkeypatch.setattr(flash, "transaction", lambda *args, **kwargs: None)

  def reg_read(addr, length=1):
    reads.append((addr, length))
    return bytes(length)

  monkeypatch.setattr(flash, "reg_read", reg_read)

  assert flash.read(0, 130) == bytes(130)
  assert reads == [(0x7000, 64), (0x7040, 64), (0x7080, 2)]
