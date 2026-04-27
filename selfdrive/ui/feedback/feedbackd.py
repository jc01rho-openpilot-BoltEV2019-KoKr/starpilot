#!/usr/bin/env python3
import cereal.messaging as messaging
from openpilot.common.params import Params
from openpilot.common.swaglog import cloudlog
from cereal import car
from openpilot.system.micd import SAMPLE_RATE, SAMPLE_BUFFER

FEEDBACK_MAX_DURATION = 10.0
ButtonType = car.CarState.ButtonEvent.Type


def main():
  params = Params()
  params_memory = Params(memory=True)
  pm = messaging.PubMaster(['userBookmark', 'audioFeedback'])
  sm = messaging.SubMaster(['rawAudioData', 'bookmarkButton', 'carState'])
  should_record_audio = False
  block_num = 0
  waiting_for_release = False
  early_stop_triggered = False
  last_wheel_bookmark_counter = params_memory.get_int("WheelButtonBookmarkCounter")

  while True:
    sm.update()
    bookmark_requests = 0

    # TODO: https://github.com/commaai/openpilot/issues/36015
    if False and sm.updated['carState'] and sm['carState'].canValid:
      for be in sm['carState'].buttonEvents:
        if be.type == ButtonType.lkas:
          if be.pressed:
            if not should_record_audio:
              if params.get_bool("RecordAudioFeedback"):  # Start recording on first press if toggle set
                should_record_audio = True
                block_num = 0
                waiting_for_release = False
                early_stop_triggered = False
                cloudlog.info("LKAS button pressed - starting 10-second audio feedback")
              else:
                bookmark_requests += 1  # immediately send bookmark if toggle false
                cloudlog.info("LKAS button pressed - bookmarking")
            elif should_record_audio and not waiting_for_release:  # Wait for release of second press to stop recording early
              waiting_for_release = True
          elif waiting_for_release:  # Second press released
            waiting_for_release = False
            early_stop_triggered = True
            cloudlog.info("LKAS button released - ending recording early")

    if should_record_audio and sm.updated['rawAudioData']:
      raw_audio = sm['rawAudioData']
      msg = messaging.new_message('audioFeedback', valid=True)
      msg.audioFeedback.audio.data = raw_audio.data
      msg.audioFeedback.audio.sampleRate = raw_audio.sampleRate
      msg.audioFeedback.blockNum = block_num
      block_num += 1
      if (block_num * SAMPLE_BUFFER / SAMPLE_RATE) >= FEEDBACK_MAX_DURATION or early_stop_triggered:  # Check for timeout or early stop
        bookmark_requests += 1  # send bookmark at end of audio segment
        should_record_audio = False
        early_stop_triggered = False
        cloudlog.info("10-second recording completed or second button press - stopping audio feedback")
      pm.send('audioFeedback', msg)

    if sm.updated['bookmarkButton']:
      cloudlog.info("Bookmark button pressed!")
      bookmark_requests += 1

    wheel_bookmark_counter = params_memory.get_int("WheelButtonBookmarkCounter")
    if wheel_bookmark_counter > last_wheel_bookmark_counter:
      bookmark_requests += wheel_bookmark_counter - last_wheel_bookmark_counter
      last_wheel_bookmark_counter = wheel_bookmark_counter
      cloudlog.info("Wheel button bookmark requested!")

    for _ in range(bookmark_requests):
      msg = messaging.new_message('userBookmark', valid=True)
      pm.send('userBookmark', msg)


if __name__ == '__main__':
  main()
