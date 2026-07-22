from openpilot.selfdrive.ui import stall_monitor


def test_stall_report_is_sent_to_bugsink(monkeypatch, tmp_path):
  report = {}

  def capture_message(message, **kwargs):
    report["message"] = message
    report.update(kwargs)

  monkeypatch.setattr(stall_monitor, "_capture_message", capture_message)

  monitor = stall_monitor.UIStallMonitor("raylib_ui")
  monitor._dump_dir = tmp_path
  dump = "full thread dump"
  dump_path = monitor._write_dump(dump)
  monitor._report_stall(dump, dump_path, "gui_app.present_end", 5.001, 4.999)

  assert report["message"] == "raylib UI main loop stalled"
  assert report["tags"] == {"ui_stall_name": "raylib_ui", "ui_stall_phase": "gui_app.present_end"}
  assert report["extras"]["stalled_for_s"] == 5.001
  assert report["extras"]["phase_for_s"] == 4.999
  assert "test_stall_report_is_sent_to_bugsink" in report["extras"]["main_thread_stack"]
  assert report["extras"]["thread_dump"] == dump
  assert report["attachment_path"] == dump_path
