#include <EventClock.hpp>
#include <Rtc.hpp>
#include <algorithm>

std::shared_ptr<Event> EventClock::setAbsoluteAlarm(const DateTime &dateTime,
  EventHandlerFunction handler, uint32_t duration, EventTearDownFunction tearDown)
{
  return _addEvent(std::make_shared<AbsoluteAlarm>(dateTime, handler, duration, tearDown));
}

std::shared_ptr<Event> EventClock::setRecurringAlarm(uint8_t days, uint8_t hour, uint8_t minute,
  uint8_t second, EventHandlerFunction handler, uint32_t duration, EventTearDownFunction tearDown)
{
  return _addEvent(
    std::make_shared<RecurringAlarm>(days, hour, minute, second, handler, duration, tearDown));
}

std::shared_ptr<Event> EventClock::setInterval(const TimeSpan &timeSpan,
  EventHandlerFunction handler, uint32_t duration, EventTearDownFunction tearDown)
{
  return _addEvent(std::make_shared<Interval>(timeSpan, handler, duration, tearDown));
}

void EventClock::removeEvent(const std::shared_ptr<Event> &event)
{
  _events.erase(std::remove(_events.begin(), _events.end(), event));
}

void EventClock::handleEvents()
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
    }
  }
}

std::shared_ptr<Event> EventClock::_addEvent(const std::shared_ptr<Event> &event)
{
  _events.emplace_back(event);
  return event;
}

EventClock eventClock;
