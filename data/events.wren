class Event {
  construct new() {
    _event_type = null
  }
  construct newText(text) {
    _event_type = "text"
    _content = text
  }
  event_type {_event_type}
  text { _content }
}


class EventsHandler {
  construct new() {
    _events = [null, null, null, Event.new(), null, Event.new(), null, Event.newText("Hello")]
    _i = 0
  }
  poll_events() {
    Fiber.yield(_events[_i])
    _i = _i + 1
    _i = _i % _events.count
  }
  static getFiber() {
    var handler = this.new()

    return Fiber.new {
      while(true) {
        handler.poll_events()
      }
    }
  }
} 
