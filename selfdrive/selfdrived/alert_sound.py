from cereal import log


AudibleAlert = log.SelfdriveState.AudibleAlert


def filter_forcing_stop_alert_sound(alert_type, audible_alert, forcing_stop, chime_played):
  is_forcing_stop_alert = str(alert_type or "").startswith("forcingStop/")

  if not forcing_stop:
    # Silence the alert manager's short holdover so the next force-stop cycle
    # starts from a clean sound transition.
    return (AudibleAlert.none if is_forcing_stop_alert else audible_alert), False

  if not is_forcing_stop_alert or audible_alert == AudibleAlert.none:
    return audible_alert, chime_played
  if chime_played:
    return AudibleAlert.none, True
  return audible_alert, True
