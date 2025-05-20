import "cloger" for Screen, Cloger
class Clock {
  construct new() {
    _tick = 0
  }
  tick() {
    _tick = _tick + 1
    Screen.draw("tick %(_tick)")
    Cloger.sleep(0.5)
    var event = Fiber.yield() // hand over to anything else
    if (event != null) {
      _tick = 0
    }
  }
  static getFiber() {
    var clock = this.new()
    return Fiber.new {
      while (true) {
        clock.tick()
      }
    }
  }
}
