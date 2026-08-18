import importlib.util
from pathlib import Path
from unittest.mock import MagicMock, patch  # noqa: TID251 - mocks are required to guarantee no hardware access


MODULE_PATH = Path(__file__).parents[1] / "rivian_long_flasher.py"
MODULE_SPEC = importlib.util.spec_from_file_location("rivian_long_flasher", MODULE_PATH)
assert MODULE_SPEC is not None and MODULE_SPEC.loader is not None
flasher = importlib.util.module_from_spec(MODULE_SPEC)
MODULE_SPEC.loader.exec_module(flasher)


def _external_black_panda(signature: bytes = b"current", bootstub: bool = False):
  panda = MagicMock()
  panda.is_internal.return_value = False
  panda.get_type.return_value = b"\x03"
  panda.get_signature.return_value = signature
  panda.bootstub = bootstub
  return panda


def test_current_rivian_bridge_uses_bridge_flash_path():
  panda = _external_black_panda(signature=b"expected")
  with patch.object(flasher, "_is_rivian", return_value=True), \
       patch.object(flasher.os.path, "isfile", return_value=True), \
       patch.object(flasher, "Panda", wraps=flasher.Panda) as panda_class, \
       patch.object(flasher, "_flash_panda") as flash_panda:
    panda_class.return_value = panda
    panda_class.HW_TYPE_BLACK = b"\x03"
    panda_class.usb_list.return_value = ["bridge"]
    panda_class.get_signature_from_firmware.return_value = b"expected"

    assert flasher.prepare_rivian_bridge(["internal", "bridge"]) == {"bridge"}
    flash_panda.assert_called_once_with(panda)
    panda.close.assert_called_once()


def test_outdated_rivian_bridge_uses_bridge_flash_path():
  panda = _external_black_panda(signature=b"unexpected")
  with patch.object(flasher, "_is_rivian", return_value=True), \
       patch.object(flasher.os.path, "isfile", return_value=True), \
       patch.object(flasher, "Panda", wraps=flasher.Panda) as panda_class, \
       patch.object(flasher, "_flash_panda") as flash_panda:
    panda_class.return_value = panda
    panda_class.HW_TYPE_BLACK = b"\x03"
    panda_class.usb_list.return_value = ["bridge"]
    panda_class.get_signature_from_firmware.return_value = b"expected"

    # An unknown firmware image cannot be safely identified as the bridge and
    # must be left to explicit provisioning instead of being overwritten.
    assert flasher.prepare_rivian_bridge(["internal", "bridge"]) == {"bridge"}
    flash_panda.assert_not_called()


def test_non_rivian_matching_bridge_is_reserved_without_flashing():
  panda = _external_black_panda(signature=b"expected")
  with patch.object(flasher, "_is_rivian", return_value=False), \
       patch.object(flasher.os.path, "isfile", return_value=True), \
       patch.object(flasher, "Panda", wraps=flasher.Panda) as panda_class, \
       patch.object(flasher, "_flash_panda") as flash_panda:
    panda_class.return_value = panda
    panda_class.HW_TYPE_BLACK = b"\x03"
    panda_class.usb_list.return_value = ["bridge"]
    panda_class.get_signature_from_firmware.return_value = b"expected"

    assert flasher.prepare_rivian_bridge(["internal", "bridge"]) == {"bridge"}
    flash_panda.assert_not_called()


def test_non_rivian_external_black_panda_is_not_misidentified():
  panda = _external_black_panda(signature=b"unexpected")
  with patch.object(flasher, "_is_rivian", return_value=False), \
       patch.object(flasher.os.path, "isfile", return_value=True), \
       patch.object(flasher, "Panda", wraps=flasher.Panda) as panda_class, \
       patch.object(flasher, "_flash_panda") as flash_panda:
    panda_class.return_value = panda
    panda_class.HW_TYPE_BLACK = b"\x03"
    panda_class.usb_list.return_value = ["external"]
    panda_class.get_signature_from_firmware.return_value = b"expected"

    assert flasher.prepare_rivian_bridge(["internal", "external"]) == set()
    flash_panda.assert_not_called()


def test_bootstub_external_black_panda_is_not_misidentified():
  panda = _external_black_panda(signature=b"expected", bootstub=True)
  with patch.object(flasher, "_is_rivian", return_value=True), \
       patch.object(flasher.os.path, "isfile", return_value=True), \
       patch.object(flasher, "Panda", wraps=flasher.Panda) as panda_class, \
       patch.object(flasher, "_flash_panda") as flash_panda:
    panda_class.return_value = panda
    panda_class.HW_TYPE_BLACK = b"\x03"
    panda_class.usb_list.return_value = ["bridge"]
    panda_class.get_signature_from_firmware.return_value = b"expected"

    assert flasher.prepare_rivian_bridge(["bridge"]) == {"bridge"}
    flash_panda.assert_not_called()
