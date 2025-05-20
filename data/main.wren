import "clock" for Clock
import "cloger" for Screen, Cloger
import "events" for EventsHandler
class Manager {
  construct new() {
    _clockFiber = Clock.getFiber()
    _eventsHandlerFiber = EventsHandler.getFiber()
    _currentAppFiber = null
  }  
  start() {
    while (true) {
      var event = _eventsHandlerFiber.call()
      if (event != null) {
        if (event.event_type == "text") {
          Screen.tell(event.text)
          event = null
        }
        
      }
      if (_currentAppFiber != null) {
        _currentAppFiber.call(event)
      } else {
        _clockFiber.call(event)      
      }
    }
  }
}

var manager = Manager.new()
manager.start()

