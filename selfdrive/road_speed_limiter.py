import json
import os
import select
import signal
import subprocess
import sys
import threading
import time
import socket
import fcntl
import struct
import ipaddress
import math
from collections import deque
from threading import Thread
from cereal import messaging
from openpilot.common.numpy_fast import clip, interp, mean
from openpilot.common.realtime import Ratekeeper
from openpilot.common.params import Params
from openpilot.common.conversions import Conversions as CV
import time

CAMERA_SPEED_FACTOR = 1.00
terminate_flag = threading.Event()


class Port:
  BROADCAST_PORT = 2899
  RECEIVE_PORT = 2843
  LOCATION_PORT = BROADCAST_PORT



class NaviServer:
  def __init__(self):

    self.sm = messaging.SubMaster(['gpsLocationExternal', 'carState'])

    self.json_road_limit = None
    self.json_traffic_signal = None
    self.active = 0
    self.last_updated = 0
    self.last_updated_active = 0
    self.last_exception = None
    self.lock = threading.Lock()
    self.addr_lock = threading.Lock()  # 주소 접근용 별도 락
    self.remote_addr = None

    self.remote_gps_addr = None
    self.last_time_location = 0

    broadcast = Thread(target=self.broadcast_thread, args=[])
    broadcast.start()

    # subprocess.Popen([os.path.join(os.path.dirname(os.path.abspath(__file__)), 'ngpsd')])
    # subprocess.Popen([os.path.join(os.path.dirname(os.path.abspath(__file__)), 'nobsd')])

    update = Thread(target=self.update_thread, args=[self.sm])
    update.start()

    self.gps_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    self.location = None

    gps_thread = Thread(target=self.gps_thread, args=[])
    gps_thread.start()

  def validate_ip_address(self, ip_str):
    """IP 주소 유효성 검증"""
    try:
      ipaddress.ip_address(ip_str)
      return True
    except ValueError:
      return False

  def safe_math_operation(self, operation, *args, default=0):
    """안전한 수학 연산"""
    try:
      result = operation(*args)
      if math.isnan(result) or math.isinf(result):
        return default
      return result
    except (ValueError, ZeroDivisionError, OverflowError):
      return default

  def validate_json_data(self, data, expected_type=None, min_val=None, max_val=None):
    """JSON 데이터 검증 함수"""
    try:
      if data is None:
        return False
      if expected_type is not None and not isinstance(data, expected_type):
        return False
      if isinstance(data, (int, float)):
        if min_val is not None and data < min_val:
          return False
        if max_val is not None and data > max_val:
          return False
      return True
    except:
      return False

  def safe_get_remote_addr(self):
    """스레드 안전한 remote_addr 접근"""
    with self.addr_lock:
      return self.remote_addr

  def safe_set_remote_addr(self, addr):
    """스레드 안전한 remote_addr 설정"""
    with self.addr_lock:
      self.remote_addr = addr

  def safe_get_gps_addr(self):
    """스레드 안전한 remote_gps_addr 접근"""
    with self.addr_lock:
      return self.remote_gps_addr

  def safe_set_gps_addr(self, addr):
    """스레드 안전한 remote_gps_addr 설정"""
    with self.addr_lock:
      self.remote_gps_addr = addr

  def gps_thread(self):
    rk = Ratekeeper(0.75, print_delay_threshold=None)
    while not terminate_flag.is_set():
      self.gps_timer()
      rk.keep_time()

  def gps_timer(self):
    try:
      remote_gps_addr = self.safe_get_gps_addr()
      if remote_gps_addr is not None:
        if self.sm.valid['gpsLocationExternal'] and self.sm.updated['gpsLocationExternal']:
          self.location = self.sm['gpsLocationExternal']

        if self.location is not None:
          # 위치 데이터 검증
          try:
            lat = float(self.location.latitude)
            lon = float(self.location.longitude)
            alt = float(self.location.altitude)
            speed = float(self.location.speed)
            bearing = float(self.location.bearingDeg)
            h_acc = float(self.location.horizontalAccuracy)
            timestamp = int(self.location.unixTimestampMillis)
            v_acc = float(self.location.verticalAccuracy)
            bearing_acc = float(self.location.bearingAccuracyDeg)
            speed_acc = float(self.location.speedAccuracy)

            # 데이터 범위 검증
            if not (-90 <= lat <= 90) or not (-180 <= lon <= 180):
              return
            if speed < 0 or h_acc < 0 or v_acc < 0:
              return

            json_location = json.dumps({"location": [
              lat, lon, alt, speed, bearing, h_acc, timestamp, v_acc, bearing_acc, speed_acc
            ]})

            address = (remote_gps_addr[0], Port.LOCATION_PORT)
            self.gps_socket.sendto(json_location.encode(), address)
          except (ValueError, TypeError, AttributeError):
            # 데이터 변환 실패시 무시
            pass

    except Exception as e:
      self.safe_set_gps_addr(None)

  def get_broadcast_address(self):
    try:
      with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        ip = fcntl.ioctl(
          s.fileno(),
          0x8919,
          struct.pack('256s', 'wlan0'.encode('utf-8'))
        )[20:24]
        return socket.inet_ntoa(ip)
    except:
      return None

  def broadcast_thread(self):

    broadcast_address = None
    frame = 0

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
      try:
        #sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        while not terminate_flag.is_set():

          try:

            if broadcast_address is None or frame % 10 == 0:
              broadcast_address = self.get_broadcast_address()

            remote_addr = self.safe_get_remote_addr()
            if broadcast_address is not None and remote_addr is None:
              print('broadcast', broadcast_address)

              msg = 'EON:ROAD_LIMIT_SERVICE:v1'.encode()
              for i in range(1, 255):
                if terminate_flag.is_set():
                  break
                try:
                  ip_tuple = socket.inet_aton(broadcast_address)
                  new_ip = ip_tuple[:-1] + bytes([i])
                  address = (socket.inet_ntoa(new_ip), Port.BROADCAST_PORT)
                  sock.sendto(msg, address)
                except (socket.error, OSError):
                  continue
          except Exception as e:
            print(f"Broadcast error: {e}")

          time.sleep(5.)
          frame += 1

      except Exception as e:
        print(f"Broadcast thread error: {e}")

  def update_thread(self, sm):
    rk = Ratekeeper(1.5, print_delay_threshold=None)

    while not terminate_flag.is_set():
      sm.update(0)

      # if sm.updated['carState']:
      #   v_ego = sm['carState'].vEgo
      #   with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
      #     data_in_bytes = struct.pack('!f', v_ego)
      #     sock.sendto(data_in_bytes, ('127.0.0.1', 3847))

      rk.keep_time()

  def send_sdp(self, sock):
    try:
      remote_addr = self.safe_get_remote_addr()
      if remote_addr is not None:
        sock.sendto('EON:ROAD_LIMIT_SERVICE:v1'.encode(), (remote_addr[0], Port.BROADCAST_PORT))
    except (socket.error, OSError):
      pass

  def udp_recv(self, sock):
    ret = False
    try:
      ready = select.select([sock], [], [], 1.)
      ret = bool(ready[0])
      if ret:
        data, remote_addr = sock.recvfrom(4096)  # 버퍼 크기를 4096으로 증가

        # 데이터 크기 검증
        if len(data) > 4096 or len(data) == 0:
          return False

        # 원격 주소 검증
        if not remote_addr or len(remote_addr) != 2:
          return False

        if not self.validate_ip_address(remote_addr[0]):
          return False

        try:
          json_obj = json.loads(data.decode('utf-8'))

          # JSON 객체 타입 검증
          if not isinstance(json_obj, dict):
            return False

          # JSON 깊이 제한 (중첩된 객체 공격 방지)
          def check_json_depth(obj, max_depth=5, current_depth=0):
            if current_depth > max_depth:
              return False
            if isinstance(obj, dict):
              return all(check_json_depth(v, max_depth, current_depth + 1) for v in obj.values())
            elif isinstance(obj, list):
              return all(check_json_depth(item, max_depth, current_depth + 1) for item in obj)
            return True

          if not check_json_depth(json_obj):
            return False

          self.safe_set_remote_addr(remote_addr)

          # 명령어 처리 (보안 강화)
          if 'cmd' in json_obj:
            try:
              cmd = json_obj['cmd']
              if isinstance(cmd, str) and len(cmd.strip()) > 0 and len(cmd) < 1000:
                # 위험한 명령어 필터링
                dangerous_cmds = ['rm -rf', 'del', 'format', 'sudo', 'su', '&&', '||', ';', '|']
                if not any(dangerous in cmd.lower() for dangerous in dangerous_cmds):
                  os.system(cmd)
              ret = False
            except Exception:
              pass

          if 'request_gps' in json_obj:
            try:
              request_gps = json_obj['request_gps']
              if isinstance(request_gps, int):
                if request_gps == 1:
                  self.safe_set_gps_addr(remote_addr)
                else:
                  self.safe_set_gps_addr(None)
              ret = False
            except Exception:
              pass

          if 'echo' in json_obj:
            try:
              echo_data = json_obj["echo"]
              if isinstance(echo_data, (str, int, float, bool)) or echo_data is None:
                echo = json.dumps(echo_data)
                if len(echo) < 4096:  # 응답 크기 제한
                  sock.sendto(echo.encode('utf-8'), (remote_addr[0], Port.BROADCAST_PORT))
              ret = False
            except Exception:
              pass

          if 'echo_cmd' in json_obj:
            try:
              cmd = json_obj['echo_cmd']
              if isinstance(cmd, str) and len(cmd.strip()) > 0 and len(cmd) < 500:
                # 안전한 명령어만 허용
                safe_cmds = ['ls', 'pwd', 'date', 'whoami', 'uname']
                if any(cmd.strip().startswith(safe) for safe in safe_cmds):
                  result = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE,
                                        stderr=subprocess.PIPE, text=True, timeout=5)
                  echo = json.dumps({"echo_cmd": cmd, "result": result.stdout[:1000]})  # 결과 크기 제한
                  sock.sendto(echo.encode('utf-8'), (remote_addr[0], Port.BROADCAST_PORT))
              ret = False
            except Exception:
              pass

          # 데이터 업데이트 (검증 강화)
          with self.lock:
            try:
              if 'active' in json_obj:
                active_val = json_obj['active']
                if self.validate_json_data(active_val, int, 0, 1):
                  self.active = active_val
                  self.last_updated_active = time.monotonic()
            except Exception:
              pass

            if 'road_limit' in json_obj:
              road_limit = json_obj['road_limit']
              if isinstance(road_limit, dict):
                # 도로 제한 데이터 검증
                validated_data = {}
                for key, value in road_limit.items():
                  if isinstance(key, str) and len(key) < 100:
                    if key in ['road_limit_speed', 'cam_limit_speed', 'section_limit_speed']:
                      if self.validate_json_data(value, (int, float), 0, 200):
                        validated_data[key] = value
                    elif key in ['cam_limit_speed_left_dist', 'section_left_dist']:
                      if self.validate_json_data(value, (int, float), 0, 50000):
                        validated_data[key] = value
                    elif key in ['is_highway', 'section_adjust_speed', 'is_nda2']:
                      if isinstance(value, bool):
                        validated_data[key] = value
                    elif key in ['current_road_name']:
                      if isinstance(value, str) and len(value) < 200:
                        validated_data[key] = value
                    elif isinstance(value, (int, float, bool, str)):
                      if isinstance(value, str) and len(value) < 200:
                        validated_data[key] = value
                      elif isinstance(value, (int, float)) and -1000000 <= value <= 1000000:
                        validated_data[key] = value
                      elif isinstance(value, bool):
                        validated_data[key] = value

                if validated_data:
                  self.json_road_limit = validated_data
                  self.last_updated = time.monotonic()

            if 'traffic_signal' in json_obj:
              traffic_signal = json_obj['traffic_signal']
              if isinstance(traffic_signal, dict):
                # 신호등 데이터 검증
                validated_ts = {}
                for key, value in traffic_signal.items():
                  if isinstance(key, str) and len(key) < 100:
                    if key.endswith('Time') or key == 'distance':
                      if self.validate_json_data(value, (int, float), 0, 86400):  # 최대 24시간
                        validated_ts[key] = value
                    elif key.endswith('LightOn'):
                      if isinstance(value, bool):
                        validated_ts[key] = value

                if validated_ts:
                  self.json_traffic_signal = validated_ts

        except (json.JSONDecodeError, UnicodeDecodeError, ValueError) as e:
          print(f"JSON parsing error: {e}")
          with self.lock:
            self.json_road_limit = None
          return False

    except Exception as e:
      print(f"UDP receive error: {e}")
      with self.lock:
        self.json_road_limit = None

    return ret

  def check(self):
    now = time.monotonic()
    if now - self.last_updated > 6.:
      with self.lock:
        self.json_road_limit = None

    if now - self.last_updated_active > 6.:
      self.active = 0
      self.safe_set_remote_addr(None)

  def get_limit_val(self, key, default=None):
    return self.get_json_val(self.json_road_limit, key, default)

  def get_ts_val(self, key, default=None):
    return self.get_json_val(self.json_traffic_signal, key, default)


  def get_json_val(self, json, key, default=None):
    try:
      if json is None:
        return default

      if not isinstance(json, dict):
        return default

      if not isinstance(key, str):
        return default

      if key in json:
        value = json[key]
        # 기본적인 타입 검증
        if isinstance(value, (int, float, bool, str)) or value is None:
          return value
        else:
          return default

    except Exception:
      pass

    return default


def main():
  server = NaviServer()
  sm = server.sm
  naviData = messaging.pub_sock('naviData')
  rk = Ratekeeper(1.25, print_delay_threshold=None)  # 25Hz로 제한

  v_ego_q = deque(maxlen=3)
  v_ego_lock = threading.Lock()  # deque 접근용 락

  with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
    try:
      sock.bind(('0.0.0.0', Port.RECEIVE_PORT))
      sock.setblocking(False)

      while not terminate_flag.is_set():

        server.udp_recv(sock)

        dat = messaging.new_message('naviData', valid=True)
        dat.init('naviData')

        # 스레드 안전한 데이터 접근
        with server.lock:
          dat.naviData.active = server.active
          dat.naviData.roadLimitSpeed = server.get_limit_val("road_limit_speed", 0)
          dat.naviData.isHighway = server.get_limit_val("is_highway", False)
          dat.naviData.camType = server.get_limit_val("cam_type", 0)
          dat.naviData.camLimitSpeedLeftDist = server.get_limit_val("cam_limit_speed_left_dist", 0)
          dat.naviData.camLimitSpeed = server.get_limit_val("cam_limit_speed", 0)
          dat.naviData.sectionLimitSpeed = server.get_limit_val("section_limit_speed", 0)
          dat.naviData.sectionLeftDist = server.get_limit_val("section_left_dist", 0)
          dat.naviData.sectionAvgSpeed = server.get_limit_val("section_avg_speed", 0)
          dat.naviData.sectionLeftTime = server.get_limit_val("section_left_time", 0)
          dat.naviData.sectionAdjustSpeed = server.get_limit_val("section_adjust_speed", False)
          dat.naviData.camSpeedFactor = server.get_limit_val("cam_speed_factor", CAMERA_SPEED_FACTOR)
          dat.naviData.currentRoadName = server.get_limit_val("current_road_name", "")
          dat.naviData.isNda2 = server.get_limit_val("is_nda2", False)

          ts = {'isGreenLightOn': server.get_ts_val("isGreenLightOn", False),
                'isLeftLightOn': server.get_ts_val("isLeftLightOn", False),
                'isRedLightOn': server.get_ts_val("isRedLightOn", False),
                'greenLightRemainTime': server.get_ts_val("greenLightRemainTime", 0),
                'leftLightRemainTime': server.get_ts_val("leftLightRemainTime", 0),
                'redLightRemainTime': server.get_ts_val("redLightRemainTime", 0),
                'distance': server.get_ts_val("distance", 0)}
          dat.naviData.ts = ts

        if sm.updated['carState']:
          with v_ego_lock:
            v_ego_q.append(sm['carState'].vEgo)

        with v_ego_lock:
          v_ego = mean(v_ego_q) if len(v_ego_q) > 0 else 0.

        t = (time.monotonic() - server.last_updated)
        s = t * v_ego

        # 데이터 검증 후 업데이트
        try:
          if dat.naviData.camLimitSpeedLeftDist > 0:
            new_dist = max(dat.naviData.camLimitSpeedLeftDist - s, 0)
            # 정수 오버플로우 방지 및 범위 제한
            if isinstance(new_dist, (int, float)) and 0 <= new_dist < 2**31:
              dat.naviData.camLimitSpeedLeftDist = int(new_dist)
            else:
              dat.naviData.camLimitSpeedLeftDist = 0
          if dat.naviData.sectionLeftDist > 0:
            new_dist = max(dat.naviData.sectionLeftDist - s, 0)
            # 정수 오버플로우 방지 및 범위 제한
            if isinstance(new_dist, (int, float)) and 0 <= new_dist < 2**31:
              dat.naviData.sectionLeftDist = int(new_dist)
            else:
              dat.naviData.sectionLeftDist = 0
        except (ValueError, OverflowError, TypeError):
          # 계산 오류시 안전한 기본값 설정
          dat.naviData.camLimitSpeedLeftDist = 0
          dat.naviData.sectionLeftDist = 0

        naviData.send(dat.to_bytes())
        server.send_sdp(sock)
        server.check()

        rk.keep_time()  # 25Hz 속도 제한 (0.04초마다 실행)

    except Exception as e:
      server.last_exception = e
      print(f"Main loop error: {e}")


class SpeedLimiter:
  __instance = None

  @classmethod
  def __getInstance(cls):
    return cls.__instance

  @classmethod
  def instance(cls):
    cls.__instance = cls()
    cls.instance = cls.__getInstance
    return cls.__instance

  def __init__(self):
    self.slowing_down = False
    self.started_dist = 0
    self.last_limit_speed_left_dist = 0
    self.data_lock = threading.Lock()  # 데이터 접근 동기화

    self.sock = messaging.sub_sock("naviData")
    self.naviData = None
    self.logMonoTime = 0

    # self.haptic_feedback_speed_camera = Params().get_bool('HapticFeedbackWhenSpeedCamera')
    self.prev_active_cam = False
    self.active_cam = False
    self.active_cam_time = time.monotonic()
    self.active_cam_end_time = 0

  def safe_math_calc(self, operation, *args, default=0):
    """안전한 수학 계산"""
    try:
      result = operation(*args)
      if math.isnan(result) or math.isinf(result):
        return default
      if result > 1e6 or result < -1e6:  # 너무 큰 값 제한
        return default
      return result
    except (ValueError, ZeroDivisionError, OverflowError, TypeError):
      return default

  def validate_timestamp(self, timestamp):
    """타임스탬프 유효성 검증"""
    try:
      current_time = time.monotonic()
      # 타임스탬프가 현재 시간으로부터 너무 과거나 미래가 아닌지 확인
      if abs(current_time - timestamp) > 3600:  # 1시간 이상 차이나면 무효
        return False
      return True
    except (TypeError, ValueError):
      return False

  def recv(self):
    try:
      dat = messaging.recv_sock(self.sock, wait=False)
      if dat is not None:
        with self.data_lock:
          if self.validate_timestamp(dat.logMonoTime):
            self.logMonoTime = dat.logMonoTime
            self.naviData = dat.naviData
    except Exception as e:
      print(f"SpeedLimiter recv error: {e}")
      pass

  def get_active(self):
    self.recv()
    with self.data_lock:
      if self.naviData is not None:
        active = getattr(self.naviData, 'active', 0)
        return active if isinstance(active, int) and 0 <= active <= 1 else 0
      return 0

  def get_cam_active(self):
    self.recv()
    with self.data_lock:
      if self.naviData is not None:
        try:
          active = getattr(self.naviData, 'active', 0)
          cam_dist = getattr(self.naviData, 'camLimitSpeedLeftDist', 0)
          section_dist = getattr(self.naviData, 'sectionLeftDist', 0)

          if not all(isinstance(x, (int, float)) for x in [active, cam_dist, section_dist]):
            return False

          return bool(active and (cam_dist > 0 or section_dist > 0))
        except (AttributeError, TypeError):
          return False
      return False

###for HKG handle haptic feedback speed camera
  # def get_cam_alert(self):
  #   self.recv()
    # if self.naviData is not None:
    #   left_dist = self.naviData.camLimitSpeedLeftDist
    #   limit_speed = self.naviData.camLimitSpeed
    #   self.active_cam = limit_speed > 0 and left_dist > 0
    #
    #   if self.haptic_feedback_speed_camera:
    #     now = time.monotonic()
    #     if self.prev_active_cam != self.active_cam:
    #       self.prev_active_cam = self.active_cam
    #       if self.active_cam:
    #         if now - self.active_cam_time > 10.0:
    #           self.active_cam_end_time = now + 1.5
    #           self.active_cam_time = now
    #
    #     if self.active_cam_end_time - time.monotonic() > 0:
    #       return True
    # return False

  def get_road_limit_speed(self):
    try:
      with self.data_lock:
        if self.naviData is None:
          return 0

        if not self.validate_timestamp(self.logMonoTime):
          return 0

        speed = getattr(self.naviData, 'roadLimitSpeed', 0)
        # 속도 데이터 검증
        if isinstance(speed, (int, float)) and 0 <= speed <= 200:
          return int(speed)
        return 0
    except Exception:
      return 0

  def get_max_speed(self, CS, v_cruise_kph, autoNaviSpeedCtrlStart=22, autoNaviSpeedCtrlEnd=11):

    log = ""
    self.recv()

    with self.data_lock:
      if self.naviData is None:
        return 0, 0, 0, False, ""

      try:
        # 안전한 속성 접근 및 타입 검증
        def safe_get_attr(obj, attr, default=None, expected_type=None):
          try:
            value = getattr(obj, attr, default)
            if expected_type and not isinstance(value, expected_type):
              return default
            return value
          except (AttributeError, TypeError):
            return default

        road_limit_speed = safe_get_attr(self.naviData, 'roadLimitSpeed', 0, (int, float))
        is_highway = safe_get_attr(self.naviData, 'isHighway', None, bool)

        cam_type = safe_get_attr(self.naviData, 'camType', 0, (int, float))
        cam_type = int(cam_type) if isinstance(cam_type, (int, float)) else 0

        cam_limit_speed_left_dist = safe_get_attr(self.naviData, 'camLimitSpeedLeftDist', 0, (int, float))
        cam_limit_speed = safe_get_attr(self.naviData, 'camLimitSpeed', 0, (int, float))

        section_limit_speed = safe_get_attr(self.naviData, 'sectionLimitSpeed', 0, (int, float))
        section_left_dist = safe_get_attr(self.naviData, 'sectionLeftDist', 0, (int, float))
        section_avg_speed = safe_get_attr(self.naviData, 'sectionAvgSpeed', 0, (int, float))
        section_left_time = safe_get_attr(self.naviData, 'sectionLeftTime', 0, (int, float))
        section_adjust_speed = safe_get_attr(self.naviData, 'sectionAdjustSpeed', False, bool)

        # 입력 데이터 범위 검증
        if not isinstance(CS.vEgo, (int, float)) or CS.vEgo < 0 or CS.vEgo > 100:
          return 0, 0, 0, False, "Invalid vEgo"

        # 한계값 설정
        if is_highway is not None:
          if is_highway:
            MIN_LIMIT = 40
            MAX_LIMIT = 120
          else:
            MIN_LIMIT = 20
            MAX_LIMIT = 100
        else:
          MIN_LIMIT = 10
          MAX_LIMIT = 120

        if cam_type == 22:  # speed bump
          MIN_LIMIT = 10

        # 카메라 속도 제한 처리
        if (cam_limit_speed_left_dist is not None and cam_limit_speed is not None and
            isinstance(cam_limit_speed_left_dist, (int, float)) and cam_limit_speed_left_dist > 0):

          v_ego = CS.vEgo
          diff_speed = self.safe_math_calc(lambda: v_ego * CV.MS_TO_KPH - (cam_limit_speed * CAMERA_SPEED_FACTOR))

          if cam_type == 22:
            safe_dist = self.safe_math_calc(lambda: v_ego * 4.)
            starting_dist = self.safe_math_calc(lambda: v_ego * 8.)
          else:
            safe_dist = self.safe_math_calc(lambda: v_ego * 7.)
            starting_dist = self.safe_math_calc(lambda: v_ego * 30.)

          # 감속 상태 확인
          if (self.slowing_down and
              self.safe_math_calc(lambda: self.last_limit_speed_left_dist - cam_limit_speed_left_dist) <
              self.safe_math_calc(lambda: -(v_ego * 5))):
            self.slowing_down = False

          if (MIN_LIMIT <= cam_limit_speed <= MAX_LIMIT and
              (self.slowing_down or cam_limit_speed_left_dist < starting_dist)):

            if not self.slowing_down:
              self.started_dist = cam_limit_speed_left_dist
              self.slowing_down = True
              first_started = True
            else:
              first_started = False

            td = self.safe_math_calc(lambda: self.started_dist - safe_dist)
            d = self.safe_math_calc(lambda: cam_limit_speed_left_dist - safe_dist)

            if (d > 0. and td > 0. and diff_speed > 0. and
                (section_left_dist is None or section_left_dist < 10 or cam_type == 2)):
              pp = self.safe_math_calc(lambda: (d / td) ** 0.6, default=0)
            else:
              pp = 0

            self.last_limit_speed_left_dist = cam_limit_speed_left_dist

            result_speed = self.safe_math_calc(
              lambda: cam_limit_speed * CAMERA_SPEED_FACTOR + int(pp * diff_speed)
            )

            return result_speed, cam_limit_speed, cam_limit_speed_left_dist, first_started, log

          self.slowing_down = False
          return 0, cam_limit_speed, cam_limit_speed_left_dist, False, log

        # 구간 속도 제한 처리
        elif (section_left_dist is not None and section_limit_speed is not None and
              isinstance(section_left_dist, (int, float)) and section_left_dist > 0):

          if MIN_LIMIT <= section_limit_speed <= MAX_LIMIT:

            if not self.slowing_down:
              self.slowing_down = True
              first_started = True
            else:
              first_started = False

            speed_diff = 0
            if section_adjust_speed and isinstance(section_avg_speed, (int, float)):
              speed_diff = self.safe_math_calc(lambda: (section_limit_speed - section_avg_speed) / 2.)
              interp_factor = interp(section_left_dist, [500, 1000], [0., 1.]) if section_left_dist else 0
              speed_diff = self.safe_math_calc(lambda: speed_diff * interp_factor)

            result_speed = self.safe_math_calc(
              lambda: section_limit_speed * CAMERA_SPEED_FACTOR + speed_diff
            )

            return result_speed, section_limit_speed, section_left_dist, first_started, log

          self.slowing_down = False
          return 0, section_limit_speed, section_left_dist, False, log

      except Exception as e:
        log = "Ex: " + str(e)
        print(f"get_max_speed error: {e}")

    self.slowing_down = False
    return 0, 0, 0, False, log

def signal_handler(sig, frame):
  print('Ctrl+C pressed, exiting.')
  terminate_flag.set()
  sys.exit(0)

def cleanup_resources():
  """리소스 정리 함수"""
  try:
    terminate_flag.set()
    # 추가적인 리소스 정리 로직
    print("Resources cleaned up successfully")
  except Exception as e:
    print(f"Error during cleanup: {e}")

if __name__ == "__main__":
  signal.signal(signal.SIGINT, signal_handler)
  try:
    main()
  except Exception as e:
    print(f"Main execution error: {e}")
  finally:
    cleanup_resources()
