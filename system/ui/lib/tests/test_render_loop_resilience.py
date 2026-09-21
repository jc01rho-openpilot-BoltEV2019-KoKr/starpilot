from openpilot.system.ui.lib import application


def _app(nav_stack):
  app = object.__new__(application.GuiApplication)
  app._nav_stack = nav_stack
  app._nav_stack_widgets_to_render = max(len(nav_stack), 1)
  app._width = 2160
  app._height = 1080
  app._widget_render_failures = {}
  return app


def test_widget_render_failure_does_not_abort_the_frame(monkeypatch):
  rendered = []

  class FailingWidget:
    def render(self, _rect):
      raise RuntimeError("onroad widget blew up")

  class HealthyWidget:
    def render(self, _rect):
      rendered.append("healthy")

  logged = []
  monkeypatch.setattr(application.cloudlog, "exception", lambda message: logged.append(message))

  app = _app([FailingWidget(), HealthyWidget()])
  app._render_widgets()

  assert rendered == ["healthy"]
  assert len(logged) == 1


def test_repeated_widget_render_failure_is_logged_once_per_widget(monkeypatch):
  class FailingWidget:
    def render(self, _rect):
      raise RuntimeError("still broken")

  logged = []
  monkeypatch.setattr(application.cloudlog, "exception", lambda message: logged.append(message))

  app = _app([FailingWidget()])
  for _ in range(10):
    app._render_widgets()

  assert len(logged) == 1


def test_widget_render_failure_is_logged_again_after_recovery(monkeypatch):
  class FlakyWidget:
    def __init__(self):
      self.should_fail = True

    def render(self, _rect):
      if self.should_fail:
        raise RuntimeError("flaky")

  logged = []
  monkeypatch.setattr(application.cloudlog, "exception", lambda message: logged.append(message))

  widget = FlakyWidget()
  app = _app([widget])

  app._render_widgets()
  widget.should_fail = False
  app._render_widgets()
  widget.should_fail = True
  app._render_widgets()

  assert len(logged) == 2


def test_nav_tick_failure_does_not_abort_the_frame(monkeypatch):
  ticked = []

  def failing_tick():
    raise RuntimeError("tick blew up")

  logged = []
  monkeypatch.setattr(application.cloudlog, "exception", lambda message: logged.append(message))

  app = object.__new__(application.GuiApplication)
  app._nav_stack_ticks = [failing_tick, lambda: ticked.append("healthy")]
  app._nav_tick_failures = {}
  app._run_nav_stack_ticks()

  assert ticked == ["healthy"]
  assert len(logged) == 1


def test_widget_render_failure_tracking_does_not_grow_without_bound(monkeypatch):
  monkeypatch.setattr(application.cloudlog, "exception", lambda _message: None)

  class FailingWidget:
    def render(self, _rect):
      raise RuntimeError("boom")

  app = _app([])
  for _ in range(application.MAX_TRACKED_RENDER_FAILURES * 3):
    app._nav_stack = [FailingWidget()]
    app._nav_stack_widgets_to_render = 1
    app._render_widgets()

  assert len(app._widget_render_failures) <= application.MAX_TRACKED_RENDER_FAILURES


def test_render_widgets_uses_full_window_rect():
  seen = []

  class RecordingWidget:
    def render(self, rect):
      seen.append((rect.x, rect.y, rect.width, rect.height))

  app = _app([RecordingWidget()])
  app._render_widgets()

  assert seen == [(0, 0, 2160, 1080)]
