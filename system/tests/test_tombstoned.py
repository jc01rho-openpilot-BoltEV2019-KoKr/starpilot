from openpilot.system import tombstoned


def test_report_tombstone_apport_ignores_hal3_direct_widthfix(tmp_path, monkeypatch):
  crash = tmp_path / "_data_agnos-compat_bin_hal3_direct_widthfix.0.crash"
  crash.write_text("\n".join([
    "ProblemType: Crash",
    "ExecutablePath: /data/agnos-compat/bin/hal3_direct_widthfix",
    "Signal: 11",
    "CoreDump: base64",
  ]))

  sentry_calls = []
  monkeypatch.setattr(tombstoned.sentry, "report_tombstone", lambda *args: sentry_calls.append(args))

  def fail_retrace(fn):
    raise AssertionError(f"ignored tombstones should not be retraced: {fn}")

  monkeypatch.setattr(tombstoned, "get_apport_stacktrace", fail_retrace)

  tombstoned.report_tombstone_apport(str(crash))

  assert sentry_calls == []
  assert not crash.exists()
