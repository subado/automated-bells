#include <EventClock.hpp>
#include <Rtc.hpp>
#include <algorithm>

#define MILLIS_PER_SECOND 1000

std::shared_ptr<Event> EventClock::setAbsoluteAlarm(const DateTime &dateTime,
  EventHandlerFunction handler)
{
  return _addEvent(std::make_shared<AbsoluteAlarm>(dateTime, handler));
}

std::shared_ptr<Event> EventClock::setRecurringAlarm(uint8_t days, uint8_t hour, uint8_t minute,
  uint8_t second, EventHandlerFunction handler)
{
  return _addEvent(std::make_shared<RecurringAlarm>(days, hour, minute, second, handler));
}

std::shared_ptr<Event> EventClock::setInterval(const TimeSpan &timeSpan,
  EventHandlerFunction handler)
{
  return _addEvent(std::make_shared<Interval>(timeSpan, handler));
}

void EventClock::removeEvent(const std::shared_ptr<Event> &event)
{
  _events.erase(std::remove(_events.begin(), _events.end(), event));
  Serial.printf("%s = %d", "_events.size()", _events.size());
}

void EventClock::handleEvents()
{
  for (auto &event : _events)
  {
    if (event->isHappen())
    {
      if (!event->_runned)
      {
        event->_runned = true;
        event->_startTime = millis();
        event->_run();
      }
      else if (event->_runned && (millis() - event->_startTime >= MILLIS_PER_SECOND))
      {
        event->_runned = false;
      }
    }
  }
}

std::shared_ptr<Event> EventClock::_addEvent(const std::shared_ptr<Event> &event)
{
  _events.emplace_back(event);
  return event;
}

EventClock eventClock;
