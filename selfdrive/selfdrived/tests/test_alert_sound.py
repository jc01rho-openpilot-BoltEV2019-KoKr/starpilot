from cereal import log

from openpilot.selfdrive.selfdrived.alert_sound import filter_forcing_stop_alert_sound


AudibleAlert = log.SelfdriveState.AudibleAlert


def test_forcing_stop_chimes_once_during_standstill_flicker():
  chime_played = False
  sounds = []

  for sound in (AudibleAlert.none, AudibleAlert.prompt, AudibleAlert.none, AudibleAlert.prompt):
    filtered_sound, chime_played = filter_forcing_stop_alert_sound(
      "forcingStop/warning",
      sound,
      forcing_stop=True,
      chime_played=chime_played,
    )
    sounds.append(filtered_sound)

  assert sounds == [AudibleAlert.none, AudibleAlert.prompt, AudibleAlert.none, AudibleAlert.none]
  assert chime_played is True


def test_forcing_stop_chime_resets_after_cycle_ends():
  sound, chime_played = filter_forcing_stop_alert_sound(
    "forcingStop/warning", AudibleAlert.prompt, forcing_stop=True, chime_played=False,
  )
  assert sound == AudibleAlert.prompt
  assert chime_played is True

  sound, chime_played = filter_forcing_stop_alert_sound(
    "forcingStop/warning", AudibleAlert.prompt, forcing_stop=False, chime_played=chime_played,
  )
  assert sound == AudibleAlert.none
  assert chime_played is False

  sound, chime_played = filter_forcing_stop_alert_sound(
    "forcingStop/warning", AudibleAlert.prompt, forcing_stop=True, chime_played=chime_played,
  )
  assert sound == AudibleAlert.prompt
  assert chime_played is True


def test_other_alert_sounds_are_not_suppressed():
  sound, chime_played = filter_forcing_stop_alert_sound(
    "greenLight/permanent", AudibleAlert.prompt, forcing_stop=True, chime_played=True,
  )

  assert sound == AudibleAlert.prompt
  assert chime_played is True
