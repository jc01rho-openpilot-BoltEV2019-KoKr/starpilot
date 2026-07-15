from openpilot.system.logmessaged import decode_record


def test_decode_record_replaces_malformed_utf8():
  assert decode_record(b'before\xffafter') == "before\ufffdafter"
