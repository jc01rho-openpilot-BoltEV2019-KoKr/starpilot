from openpilot.selfdrive.monitoring.policy import DRIVER_MONITOR_SETTINGS, DriverMonitoring, face_orientation_from_model


def face_orientation_from_net(angles_desc, pos_desc, rpy_calib):
  pitch, yaw = face_orientation_from_model(angles_desc, pos_desc, rpy_calib)
  roll = angles_desc[2] if len(angles_desc) > 2 else 0.
  return roll, pitch, yaw
