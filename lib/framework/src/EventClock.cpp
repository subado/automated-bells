#include <EventClock.hpp>
#include <Rtc.hpp>

#define MILLIS_PER_SECOND 1000

extern Rtc rtc;

EventClock::EventClock() : _wire{Wire}
{
}

EventClock::EventClock(TwoWire &wire) : _wire{wire}
{
}

void EventClock::setAlarm(const DateTime &dateTime, EventHandlerFunction handler)
{
  _events.emplace_back(std::make_unique<Alarm>(dateTime, handler));
}

void EventClock::setInterval(const TimeSpan &timeSpan, EventHandlerFunction handler)
{
  _events.emplace_back(std::make_unique<Interval>(timeSpan, handler));
}

void EventClock::handleEvents()
{
  for (auto &event : _events)
  {
    if (event->isHappen())
    {
      if (!event->runned)
      {
        event->runned = true;
        event->startTime = millis();
        event->run();
      }
      else if (event->runned && (millis() - event->startTime >= MILLIS_PER_SECOND))
      {
        event->runned = false;
      }
    }
  }
}

EventClock::Event::Event(EventHandlerFunction handler) : handler{handler}
{
}

void EventClock::Event::run()
{
  handler(rtc.now());
}

EventClock::Alarm::Alarm(const DateTime &dateTime, EventHandlerFunction handler)
    : Event(handler), dateTime{dateTime}
{
}

bool EventClock::Alarm::isHappen() const
{
  if (dateTime == rtc.now())
  {
    return true;
  }
  return false;
}

EventClock::Interval::Interval(const TimeSpan &timeSpan, EventHandlerFunction handler)
    : Event(handler), timeSpan{timeSpan}, prevTime(rtc.now())
{
}

bool EventClock::Interval::isHappen() const
{
  if (prevTime + timeSpan == rtc.now())
  {
    return true;
  }
  return false;
}

void EventClock::Interval::run()
{
  prevTime = rtc.now();
  handler(prevTime);
}

EventClock eventClock;
