#include <EventManager.hpp>
#include <Rtc.hpp>
#include <algorithm>

void EventManager::removeEvent(const Event *event)
{
  _events.erase(std::remove_if(_events.begin(), _events.end(),
    [&event](const std::unique_ptr<Event> &ptr)
    {
      return ptr.get() == event;
    }));
}

void EventManager::handleEvents()
{
  for (auto &event : _events)
  {
    if (event->isHappen() && !event->_runned)
    {
      event->_runned = true;
      event->_startTime = rtc.now().secondstime();
      event->_run();
    }
    else if (event->_runned && (rtc.now().secondstime() - event->_startTime >= event->_duration))
    {
      event->_runned = false;
      event->_tearDown();

      if (event->isSelfDestructive())
      {
        removeEvent(event.get());
      }
    }
  }
}

EventManager eventManager;
