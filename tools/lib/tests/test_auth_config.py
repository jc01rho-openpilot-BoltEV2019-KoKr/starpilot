from openpilot.tools.lib.auth_config import DEFAULT_API_HOST, KONIK_API_HOST, get_token, set_token


def test_set_token_preserves_comma_token_when_adding_konik(mocker, tmp_path):
  mocker.patch("openpilot.tools.lib.auth_config.Paths.config_root", return_value=str(tmp_path))

  set_token("comma-token", DEFAULT_API_HOST)
  set_token("konik-token", KONIK_API_HOST)

  assert get_token(DEFAULT_API_HOST) == "comma-token"
  assert get_token(KONIK_API_HOST) == "konik-token"
  assert get_token() == "comma-token"
