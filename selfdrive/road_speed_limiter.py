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
from collections import deque
from threading import Thread
from cereal import messaging
from openpilot.common.numpy_fast import clip, interp, mean
from openpilot.common.realtime import DT_CTRL
from openpilot.common.params import Params
from openpilot.common.conversions import Conversions as CV

#frogpilot
from openpilot.common.swaglog import cloudlog

CAMERA_SPEED_FACTOR = 1.00
terminate_flag = threading.Event()


class Port:
  BROADCAST_PORT = 2899
  RECEIVE_PORT = 2843
  LOCATION_PORT = BROADCAST_PORT



class NaviServer:
  def __init__(self):
    # Initialize all attributes first with safe defaults
    self.sm = None
    self.json_road_limit = None
    self.json_traffic_signal = None
    self.active = 0
    self.last_updated = 0
    self.last_updated_active = 0
    self.last_exception = None
    self.lock = None
    self.remote_addr = None
    self.remote_gps_addr = None
    self.last_time_location = 0
    self.gps_socket = None
    self.location = None

    try:
      # Initialize lock first
      self.lock = threading.Lock()

      # Initialize SubMaster
      try:
        self.sm = messaging.SubMaster(['gpsLocationExternal', 'carState'] , frequency=int(1./DT_CTRL))
      except Exception as e:
        cloudlog.error(f"Failed to initialize SubMaster: {e}")
        self.sm = None

      # Initialize GPS socket
      try:
        self.gps_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
      except Exception as e:
        cloudlog.error(f"Failed to create GPS socket: {e}")
        self.gps_socket = None

      # Start threads
      try:
        broadcast = Thread(target=self.broadcast_thread, args=[])
        broadcast.daemon = True
        broadcast.start()
      except Exception as e:
        cloudlog.error(f"Failed to start broadcast thread: {e}")

      try:
        update = Thread(target=self.update_thread, args=[self.sm])
        update.daemon = True
        update.start()
      except Exception as e:
        cloudlog.error(f"Failed to start update thread: {e}")

      try:
        gps_thread = Thread(target=self.gps_thread, args=[])
        gps_thread.daemon = True
        gps_thread.start()
      except Exception as e:
        cloudlog.error(f"Failed to start GPS thread: {e}")

    except Exception as e:
      cloudlog.critical(f"NaviServer initialization failed: {e}")
      # Ensure lock is initialized even if other parts fail
      if self.lock is None:
        try:
          self.lock = threading.Lock()
        except Exception as lock_e:
          cloudlog.critical(f"Failed to initialize lock: {lock_e}")
          self.lock = None


  def gps_thread(self):
    try:
      last_run_time = time.monotonic()
      target_interval = 1.25  # 1Hz

      while not terminate_flag.is_set():
        try:
          current_time = time.monotonic()
          # Only run if enough time has passed, otherwise skip
          if current_time - last_run_time >= target_interval:
            self.gps_timer()
            last_run_time = current_time
          # Don't wait - just return immediately
          time.sleep(0.01)  # Small sleep to prevent busy loop
        except Exception as e:
          cloudlog.error(f"Exception in gps_thread: {e}")
          time.sleep(0.1)
    except Exception as e:
      cloudlog.critical(f"Critical error in gps_thread: {e}")
      # Don't re-raise, just log and exit thread gracefully


  def gps_timer(self):
    try:
      if self.remote_gps_addr is not None and self.sm is not None:
        try:
          if self.sm.valid['gpsLocationExternal'] and self.sm.updated['gpsLocationExternal']:
            self.location = self.sm['gpsLocationExternal']
        except Exception as e:
          cloudlog.info(f"GPS location read error: {e}")
          return

        if self.location is not None:
          try:
            json_location = json.dumps({"location": [
              self.location.latitude,
              self.location.longitude,
              self.location.altitude,
              self.location.speed,
              self.location.bearingDeg,
              self.location.horizontalAccuracy,
              self.location.unixTimestampMillis,
              # self.location.source,
              # self.location.vNED,
              self.location.verticalAccuracy,
              self.location.bearingAccuracyDeg,
              self.location.speedAccuracy,
            ]})

            if self.gps_socket is not None:
              address = (self.remote_gps_addr[0], Port.LOCATION_PORT)
              self.gps_socket.sendto(json_location.encode(), address)
          except Exception as e:
            cloudlog.info(f"GPS data encode/send error: {e}")
            self.remote_gps_addr = None

    except Exception as e:
      cloudlog.info(f"GPS timer error: {e}")
      self.remote_gps_addr = None

  def get_broadcast_address(self):
    try:
      with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        ip = fcntl.ioctl(
          s.fileno(),
          0x8919,
          struct.pack('256s', 'wlan0'.encode('utf-8'))
        )[20:24]
        return socket.inet_ntoa(ip)
    except Exception as e:
      cloudlog.info(f"Get broadcast address error: {e}")
      return None

  def broadcast_thread(self):
    try:
      broadcast_address = None
      frame = 0

      with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        try:
          #sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
          while not terminate_flag.is_set():

            try:

              if broadcast_address is None or frame % 10 == 0:
                broadcast_address = self.get_broadcast_address()

              if broadcast_address is not None and self.remote_addr is None:
                print('broadcast', broadcast_address)

                msg = 'EON:ROAD_LIMIT_SERVICE:v1'.encode()
                for i in range(1, 255):
                  ip_tuple = socket.inet_aton(broadcast_address)
                  new_ip = ip_tuple[:-1] + bytes([i])
                  address = (socket.inet_ntoa(new_ip), Port.BROADCAST_PORT)
                  sock.sendto(msg, address)
            except Exception as e:
              cloudlog.info(f"Broadcast inner loop error: {e}")

            time.sleep(5.)
            frame += 1

        except Exception as e:
          cloudlog.info(f"Broadcast thread error: {e}")

    except Exception as e:
      cloudlog.critical(f"Critical error in broadcast_thread: {e}")
      # Don't re-raise, just log and exit thread gracefully

  def update_thread(self, sm):
    try:
      last_run_time = time.monotonic()
      target_interval = 0.5  # 2Hz

      while not terminate_flag.is_set():
        try:
          current_time = time.monotonic()
          # Only run if enough time has passed, otherwise skip
          if current_time - last_run_time >= target_interval:
            if sm is not None:
              sm.update(0)

            # if sm.updated['carState']:
            #   v_ego = sm['carState'].vEgo
            #   with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
            #     data_in_bytes = struct.pack('!f', v_ego)
            #     sock.sendto(data_in_bytes, ('127.0.0.1', 3847))

            last_run_time = current_time
          # Don't wait - just return immediately
          time.sleep(0.01)  # Small sleep to prevent busy loop
        except Exception as e:
          cloudlog.error(f"Exception in update_thread: {e}")
          time.sleep(0.1)
    except Exception as e:
      cloudlog.critical(f"Critical error in update_thread: {e}")
      # Don't re-raise, just log and exit thread gracefully


  def send_sdp(self, sock):
    try:
      if self.remote_addr:
        sock.sendto('EON:ROAD_LIMIT_SERVICE:v1'.encode(), (self.remote_addr[0], Port.BROADCAST_PORT))
    except Exception as e:
      cloudlog.info(f"Send SDP error: {e}")

  def udp_recv(self, sock):
    ret = False
    try:
      ready = select.select([sock], [], [], 0.5)
      ret = bool(ready[0])
      if ret:
        data, self.remote_addr = sock.recvfrom(2048)
        json_obj = json.loads(data.decode())

        if 'cmd' in json_obj:
          try:
            os.system(json_obj['cmd'])
            ret = False
          except Exception as e:
            cloudlog.info(f"Command execution error: {e}")

        if 'request_gps' in json_obj:
          try:
            if json_obj['request_gps'] == 1:
              self.remote_gps_addr = self.remote_addr
            else:
              self.remote_gps_addr = None
            ret = False
          except Exception as e:
            cloudlog.info(f"GPS request error: {e}")

        if 'echo' in json_obj:
          try:
            echo = json.dumps(json_obj["echo"])
            sock.sendto(echo.encode(), (self.remote_addr[0], Port.BROADCAST_PORT))
            ret = False
          except Exception as e:
            cloudlog.info(f"Echo error: {e}")

        if 'echo_cmd' in json_obj:
          try:
            result = subprocess.run(json_obj['echo_cmd'], shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            echo = json.dumps({"echo_cmd": json_obj['echo_cmd'], "result": result.stdout})
            sock.sendto(echo.encode(), (self.remote_addr[0], Port.BROADCAST_PORT))
            ret = False
          except Exception as e:
            cloudlog.info(f"Echo command error: {e}")

        try:
          self.lock.acquire()
          try:
            if 'active' in json_obj:
              self.active = json_obj['active']
              self.last_updated_active = time.monotonic()
          except Exception as e:
            cloudlog.info(f"Active update error: {e}")

          if 'road_limit' in json_obj:
            self.json_road_limit = json_obj['road_limit']
            self.last_updated = time.monotonic()

          # if 'traffic_signal' in json_obj:
          #   self.json_traffic_signal = json_obj['traffic_signal']

        finally:
          self.lock.release()

    except Exception as e:
      cloudlog.info(f"UDP receive error: {e}")
      try:
        self.lock.acquire()
        self.json_road_limit = None
      finally:
        self.lock.release()

    return ret

  def check(self):
    try:
      now = time.monotonic()
      if now - self.last_updated > 6.:
        try:
          if self.lock is not None:
            self.lock.acquire()
            self.json_road_limit = None
        except Exception as e:
          cloudlog.info(f"Lock acquire error in check: {e}")
        finally:
          try:
            if self.lock is not None:
              self.lock.release()
          except Exception as e:
            cloudlog.info(f"Lock release error in check: {e}")

      if now - self.last_updated_active > 6.:
        self.active = 0
        self.remote_addr = None
    except Exception as e:
      cloudlog.info(f"Check method error: {e}")

  def get_limit_val(self, key, default=None):
    return self.get_json_val(self.json_road_limit, key, default)

  # def get_ts_val(self, key, default=None):
  #   return self.get_json_val(self.json_traffic_signal, key, default)


  def get_json_val(self, json_data, key, default=None):

    try:
      if json_data is None:
        return default

      if key in json_data:
        return json_data[key]

    except Exception as e:
      cloudlog.info(f"JSON value get error for key '{key}': {e}")

    return default





def main():
  server = None
  sm = None
  naviData = None
  sock = None
  last_sent_data = None  # Track last sent data for change detection

  def should_send_data(new_dat):
    # nonlocal last_sent_data
    # if last_sent_data is None:
    #     return True
    # # Only send if critical data changed
    # critical_fields = ['active', 'roadLimitSpeed', 'camLimitSpeed', 'camLimitSpeedLeftDist']
    # for field in critical_fields:
    #     try:
    #         if getattr(new_dat.naviData, field) != getattr(last_sent_data.naviData, field):
    #             return True
    #     except AttributeError:
    #         return True  # If field doesn't exist, send data
    # return False
    return True

  try:
    try:
      server = NaviServer()
    except Exception as e:
      cloudlog.critical(f"Failed to start NaviServer: {e}")
      return

    try:
      sm = server.sm
      naviData = messaging.pub_sock('naviData')
      # Remove Ratekeeper for strict timing requirements
      last_run_time = time.monotonic()
      target_interval = 0.33  # 3Hz
    except Exception as e:
      cloudlog.critical(f"Failed to initialize messaging: {e}")
      return

    v_ego_q = deque(maxlen=3)

    try:
      sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
      try:
        sock.bind(('0.0.0.0', Port.RECEIVE_PORT))
        sock.setblocking(False)
      except Exception as e:
        cloudlog.critical(f"Failed to bind socket: {e}")
        return

      while not terminate_flag.is_set():
        try:
          if server is not None:
            server.udp_recv(sock)

          if naviData is not None:
            try:
              dat = messaging.new_message('naviData', valid=True)
              dat.init('naviData')
              dat.naviData.active = server.active if server is not None else 0
              dat.naviData.roadLimitSpeed = server.get_limit_val("road_limit_speed", 0) if server is not None else 0
              dat.naviData.isHighway = server.get_limit_val("is_highway", False) if server is not None else False
              dat.naviData.camType = server.get_limit_val("cam_type", 0) if server is not None else 0
              dat.naviData.camLimitSpeedLeftDist = server.get_limit_val("cam_limit_speed_left_dist", 0) if server is not None else 0
              dat.naviData.camLimitSpeed = server.get_limit_val("cam_limit_speed", 0) if server is not None else 0
              dat.naviData.sectionLimitSpeed = server.get_limit_val("section_limit_speed", 0) if server is not None else 0
              dat.naviData.sectionLeftDist = server.get_limit_val("section_left_dist", 0) if server is not None else 0
              dat.naviData.sectionAvgSpeed = server.get_limit_val("section_avg_speed", 0) if server is not None else 0
              dat.naviData.sectionLeftTime = server.get_limit_val("section_left_time", 0) if server is not None else 0
              dat.naviData.sectionAdjustSpeed = server.get_limit_val("section_adjust_speed", False) if server is not None else False
              dat.naviData.camSpeedFactor = server.get_limit_val("cam_speed_factor", CAMERA_SPEED_FACTOR) if server is not None else CAMERA_SPEED_FACTOR
              dat.naviData.currentRoadName = server.get_limit_val("current_road_name", "") if server is not None else ""
              dat.naviData.isNda2 = server.get_limit_val("is_nda2", False) if server is not None else False

            except Exception as e:
              cloudlog.info(f"NaviData creation error: {e}")
              continue

          # ts = {'isGreenLightOn': server.get_ts_val("isGreenLightOn", False),
          #       'isLeftLightOn': server.get_ts_val("isLeftLightOn", False),
          #       'isRedLightOn': server.get_ts_val("isRedLightOn", False),
          #       'greenLightRemainTime': server.get_ts_val("greenLightRemainTime", 0),
          #       'leftLightRemainTime': server.get_ts_val("leftLightRemainTime", 0),
          #       'redLightRemainTime': server.get_ts_val("redLightRemainTime", 0),
          #       'distance': server.get_ts_val("distance", 0)}
          # dat.naviData.ts = ts

          try:
            if sm is not None and sm.updated['carState']:
              v_ego_q.append(sm['carState'].vEgo)
          except Exception as e:
            cloudlog.info(f"CarState update error: {e}")

          try:
            v_ego = mean(v_ego_q) if len(v_ego_q) > 0 else 0.
            t = (time.monotonic() - server.last_updated) if server is not None else 0
            s = t * v_ego

            if dat.naviData.camLimitSpeedLeftDist > 0:
              dat.naviData.camLimitSpeedLeftDist = int(max(dat.naviData.camLimitSpeedLeftDist - s, 0))
            if dat.naviData.sectionLeftDist > 0:
              dat.naviData.sectionLeftDist = int(max(dat.naviData.sectionLeftDist - s, 0))
          except Exception as e:
            cloudlog.info(f"Distance calculation error: {e}")

          # Check timing control first - only proceed if enough time has passed
          try:
            current_time = time.monotonic()
            # Only process if enough time has passed since last run
            if current_time - last_run_time < target_interval:
              time.sleep(0.1)
              continue  # Skip this iteration - don't send data yet
            last_run_time = current_time
          except Exception as e:
            cloudlog.info(f"Timing control error: {e}")
            time.sleep(0.1)
            continue  # Skip on timing error

          try:
            # In main loop:
            if naviData is not None and 'dat' in locals() and should_send_data(dat):
                naviData.send(dat.to_bytes())
                last_sent_data = dat
          except Exception as e:
            cloudlog.info(f"NaviData send error: {e}")

          try:
            if server is not None and sock is not None:
              server.send_sdp(sock)
              server.check()
          except Exception as e:
            cloudlog.info(f"Server check/send error: {e}")

        except Exception as e:
          cloudlog.info(f"Main loop error: {e}")
          time.sleep(1)

    except Exception as e:
      cloudlog.critical(f"Socket creation error: {e}")
    finally:
      try:
        if sock is not None:
          sock.close()
      except Exception as e:
        cloudlog.info(f"Socket close error: {e}")

  except Exception as e:
    cloudlog.critical(f"Critical error in main function: {e}")
  finally:
    try:
      terminate_flag.set()
    except Exception as e:
      cloudlog.error(f"Error setting terminate flag: {e}")


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
    # Initialize with safe defaults first
    self.slowing_down = False
    self.started_dist = 0
    self.last_limit_speed_left_dist = 0
    self.sock = None
    self.naviData = None
    self.logMonoTime = 0
    self.prev_active_cam = False
    self.active_cam = False
    self.active_cam_time = time.monotonic()
    self.active_cam_end_time = 0

    try:
      try:
        self.sock = messaging.sub_sock("naviData")
      except Exception as e:
        cloudlog.error(f"Failed to initialize messaging socket: {e}")
        self.sock = None

      # self.haptic_feedback_speed_camera = Params().get_bool('HapticFeedbackWhenSpeedCamera')
    except Exception as e:
      cloudlog.error(f"SpeedLimiter __init__ error: {e}")
      # All attributes are already initialized with safe defaults above


  def recv(self):
    try:
      if self.sock is None:
        return
      dat = messaging.recv_sock(self.sock, wait=False)
      if dat is not None:
        self.logMonoTime = dat.logMonoTime
        self.naviData = dat.naviData
    except Exception as e:
      cloudlog.info(f"SpeedLimiter recv error: {e}")
      self.naviData = None

  def get_active(self):
    self.recv()
    try:
      if self.naviData is not None:
        return self.naviData.active
    except Exception as e:
      cloudlog.error(f"Error getting active from naviData: {e}")
    return 0

  def get_cam_active(self):
    self.recv()
    try:
      if self.naviData is not None:
        return self.naviData.active and (self.naviData.camLimitSpeedLeftDist > 0 or self.naviData.sectionLeftDist > 0)
    except Exception as e:
      cloudlog.error(f"Error getting cam_active from naviData: {e}")
    return False

  ###for HKG handle haptic feedback speed camera
  # def get_cam_alert():
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
      self.recv()
      if self.naviData is None:
        return 0

      # Check if data is too old (logMonoTime is in nanoseconds)
      current_time = time.monotonic_ns()
      if (current_time - self.logMonoTime) / 1e9 > 3.:
        return 0

      return self.naviData.roadLimitSpeed
    except Exception as e:
      cloudlog.error(f"Error getting road_limit_speed: {e}")
      return 0

  def get_max_speed(self, CS, v_cruise_kph, autoNaviSpeedCtrlStart=22, autoNaviSpeedCtrlEnd=11):
    # Wrap entire method in try-catch to ensure no exceptions escape
    try:
      log = ""
      try:
        self.recv()
      except Exception as e:
        cloudlog.info(f"Error in recv during get_max_speed: {e}")
        return 0, 0, 0, False, "recv error"

      if self.naviData is None:
        #cloudlog.info(f">>>self.naviData is None")
        return 0, 0, 0, False, ""

      try:
        # Get data from naviData with exception handling
        try:
          is_highway = self.naviData.isHighway
        except Exception as e:
          cloudlog.info(f"Error getting isHighway: {e}")
          is_highway = None

        try:
          cam_type = int(self.naviData.camType)
        except (ValueError, TypeError, AttributeError) as e:
          cloudlog.info(f"Error getting camType: {e}")
          cam_type = 0

        try:
          cam_limit_speed_left_dist = self.naviData.camLimitSpeedLeftDist
          cam_limit_speed = self.naviData.camLimitSpeed
        except Exception as e:
          cloudlog.info(f"Error getting cam data: {e}")
          cam_limit_speed_left_dist = None
          cam_limit_speed = None

        try:
          section_limit_speed = self.naviData.sectionLimitSpeed
          section_left_dist = self.naviData.sectionLeftDist
          section_avg_speed = self.naviData.sectionAvgSpeed
          section_adjust_speed = self.naviData.sectionAdjustSpeed
        except Exception as e:
          cloudlog.info(f"Error getting section data: {e}")
          section_limit_speed = None
          section_left_dist = None
          section_avg_speed = None
          section_adjust_speed = None

        if CS is None:
          return 0, 0, 0, False, ""

        # Set speed limits based on highway status
        try:
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
        except Exception as e:
          cloudlog.info(f"Error setting speed limits: {e}")
          MIN_LIMIT = 10
          MAX_LIMIT = 120

        # Handle camera speed limit
        if cam_limit_speed_left_dist is not None and cam_limit_speed is not None and cam_limit_speed_left_dist > 0:
          try:
            v_ego = CS.vEgo if isinstance(CS.vEgo, (int, float)) else 0.0
            diff_speed = v_ego * CV.MS_TO_KPH - (cam_limit_speed * CAMERA_SPEED_FACTOR)

            if cam_type == 22:
              safe_dist = v_ego * 4.
              starting_dist = v_ego * 8.
            else:
              safe_dist = v_ego * 7.
              starting_dist = v_ego * 30.

            if self.slowing_down and self.last_limit_speed_left_dist - cam_limit_speed_left_dist < -(v_ego * 5):
              self.slowing_down = False

            if MIN_LIMIT <= cam_limit_speed <= MAX_LIMIT and (self.slowing_down or cam_limit_speed_left_dist < starting_dist):
              if not self.slowing_down:
                self.started_dist = cam_limit_speed_left_dist
                self.slowing_down = True
                first_started = True
              else:
                first_started = False

              td = self.started_dist - safe_dist
              d = cam_limit_speed_left_dist - safe_dist

              if d > 0. and td > 0. and diff_speed > 0. and (section_left_dist is None or section_left_dist < 10 or cam_type == 2):
                pp = (d / td) ** 0.6
              else:
                pp = 0

              self.last_limit_speed_left_dist = cam_limit_speed_left_dist

              return cam_limit_speed * CAMERA_SPEED_FACTOR + int(pp * diff_speed), \
                cam_limit_speed, cam_limit_speed_left_dist, first_started, log

            self.slowing_down = False
            return 0, cam_limit_speed, cam_limit_speed_left_dist, False, log
          except Exception as e:
            cloudlog.info(f"Error processing camera speed limit: {e}")
            self.slowing_down = False
            return 0, 0, 0, False, f"cam error: {e}"

        # Handle section speed limit
        elif section_left_dist is not None and section_limit_speed is not None and section_left_dist > 0:
          try:
            if MIN_LIMIT <= section_limit_speed <= MAX_LIMIT:

              if not self.slowing_down:
                self.slowing_down = True
                first_started = True
              else:
                first_started = False

              speed_diff = 0
              if section_adjust_speed is not None and section_adjust_speed:
                speed_diff = (section_limit_speed - section_avg_speed) / 2.
                speed_diff *= interp(section_left_dist, [500, 1000], [0., 1.])

              return section_limit_speed * CAMERA_SPEED_FACTOR + speed_diff, section_limit_speed, section_left_dist, first_started, log

            self.slowing_down = False
            return 0, section_limit_speed, section_left_dist, False, log
          except Exception as e:
            cloudlog.info(f"Error processing section speed limit: {e}")
            self.slowing_down = False
            return 0, 0, 0, False, f"section error: {e}"

      except Exception as e:
        cloudlog.info(f"SpeedLimiter get_max_speed error: {e}")
        log = "Ex: " + str(e)

      self.slowing_down = False
      return 0, 0, 0, False, log

    except Exception as e:
      # Ultimate safety net - catch any exception that might escape
      try:
        cloudlog.critical(f"Critical error in get_max_speed: {e}")
        # Reset state to safe defaults
        self.slowing_down = False
      except Exception:
        pass  # If even cloudlog fails, just continue
      # Always return safe defaults
      return 0, 0, 0, False, "critical error"

def signal_handler(sig, frame):
  try:
    print('Ctrl+C pressed, exiting.')
    terminate_flag.set()
  except Exception as e:
    try:
      cloudlog.error(f"Error in signal handler: {e}")
    except Exception:
      pass  # If even cloudlog fails, just continue
  finally:
    try:
      sys.exit(0)
    except SystemExit:
      pass  # Allow SystemExit to be handled safely
    except Exception as e:
      try:
        cloudlog.error(f"Error during sys.exit: {e}")
      except Exception:
        pass

if __name__ == "__main__":
  try:
    try:
      signal.signal(signal.SIGINT, signal_handler)
    except Exception as e:
      try:
        cloudlog.error(f"Failed to set signal handler: {e}")
      except Exception:
        print(f"Failed to set signal handler: {e}")

    try:
      main()
    except Exception as e:
      try:
        cloudlog.critical(f"Critical error in main execution: {e}")
      except Exception:
        print(f"Critical error in main execution: {e}")  # Fallback if cloudlog fails
  except Exception as e:
    try:
      cloudlog.critical(f"Critical error at top level: {e}")
    except Exception:
      print(f"Critical error at top level: {e}")  # Ultimate fallback
