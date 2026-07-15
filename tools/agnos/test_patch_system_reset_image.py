import pytest

from tools.agnos.patch_system_reset_image import (
  COMMA_SH_DISPLAY_WAIT_PATCH_MARKER,
  comma_sh_has_expected_display_wait,
  format_debugfs_mode,
  patch_comma_sh_display_wait,
)


ORIGINAL_DISPLAY_WAIT = b'''#!/usr/bin/env bash
echo "waiting for magic"
for i in {1..200}; do
  if systemctl is-active --quiet magic && [ -S /tmp/drmfd.sock ]; then
    break
  fi
  sleep 0.1
done

if systemctl is-active --quiet magic && [ -S /tmp/drmfd.sock ]; then
  echo "magic ready after ${SECONDS}s"
else
  echo "timed out waiting for magic, ${SECONDS}s"
fi

exec /data/continue.sh
'''


def test_patch_comma_sh_display_wait_uses_available_display_service():
  patched = patch_comma_sh_display_wait(ORIGINAL_DISPLAY_WAIT)

  assert COMMA_SH_DISPLAY_WAIT_PATCH_MARKER.encode() in patched
  assert b"systemctl cat magic.service" in patched
  assert b"systemctl is-active --quiet magic" in patched
  assert b"systemctl is-active --quiet weston-ready" in patched
  assert b"[ -S /var/tmp/weston/wayland-0 ]" in patched
  assert comma_sh_has_expected_display_wait(patched)
  assert patch_comma_sh_display_wait(patched) == patched


def test_patch_comma_sh_display_wait_rejects_unknown_layout():
  with pytest.raises(RuntimeError, match="display readiness wait"):
    patch_comma_sh_display_wait(b"#!/usr/bin/env bash\nexec /data/continue.sh\n")


@pytest.mark.parametrize(("mode", "expected"), [
  ("100775", "0100775"),
  ("100644", "0100644"),
  ("040755", "040755"),
  ("120777", "0120777"),
])
def test_format_debugfs_mode(mode, expected):
  assert format_debugfs_mode(mode) == expected
