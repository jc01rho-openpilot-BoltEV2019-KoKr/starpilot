class FirstOrderFilter:
  def __init__(self, x0, rc, dt, initialized=True):
    self.x = x0
    self.dt = dt
    self.update_alpha(rc)
    self.initialized = initialized

  def update_alpha(self, rc):
    self.alpha = self.dt / (rc + self.dt)

  def update(self, x):
    if self.initialized:
      self.x = (1. - self.alpha) * self.x + self.alpha * x
    else:
      self.initialized = True
      self.x = x
    return self.x


class BounceFilter(FirstOrderFilter):
  def __init__(self, x0, rc, dt, initialized=True, bounce=2):
    self.velocity = FirstOrderFilter(0.0, 0.15, dt)
    self.bounce = bounce
    super().__init__(x0, rc, dt, initialized)

  def update(self, x):
    super().update(x)
    scale = self.dt / (1.0 / 60.0)  # tuned at 60 fps
    self.velocity.x += (x - self.x) * self.bounce * scale * self.dt
    self.velocity.update(0.0)
    if abs(self.velocity.x) < 1e-5:
      self.velocity.x = 0.0
    self.x += self.velocity.x
    return self.x


class SecondOrderFilter:
  """Cascaded two FirstOrderFilters for steeper roll-off (-40dB/decade).
  
  Use for noise-prone signals where single LPF (e.g., 0.10s) is insufficient.
  Typical: rc1=0.05s (3.2Hz) + rc2=0.02s (8Hz) → ~20dB attenuation at 5Hz.
  """
  def __init__(self, x0, rc1, rc2, dt, initialized=True):
    self.f1 = FirstOrderFilter(x0, rc1, dt, initialized)
    self.f2 = FirstOrderFilter(x0, rc2, dt, initialized)

  def update(self, x):
    return self.f2.update(self.f1.update(x))

  def reset(self, x0):
    self.f1.x = x0
    self.f2.x = x0
    self.f1.initialized = True
    self.f2.initialized = True
