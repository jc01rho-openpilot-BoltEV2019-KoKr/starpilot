from dataclasses import asdict

from openpilot.system.webrtc.helpers import StreamRequestBody


def test_stream_request_body_defaults_legacy_clients_to_road():
  body = StreamRequestBody(sdp="offer")

  assert body.init_camera == "road"
  assert body.enabled is True
  assert body.cameras == ["road"]
  assert body.bridge_services_in == []
  assert body.bridge_services_out == []


def test_stream_request_body_maps_legacy_camera_to_new_camera_list():
  body = StreamRequestBody(sdp="offer", init_camera="driver", enabled=False)

  assert body.init_camera == "driver"
  assert body.cameras == ["driver"]
  assert body.enabled is False


def test_stream_request_body_preserves_explicit_multi_camera_request():
  body = StreamRequestBody(sdp="offer", cameras=["road", "driver"])

  assert body.init_camera == "road"
  assert body.cameras == ["road", "driver"]
  assert asdict(body)["cameras"] == ["road", "driver"]
