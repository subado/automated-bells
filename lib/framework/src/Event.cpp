#include <Event.hpp>
#include <Rtc.hpp>

Event::Event(EventHandlerFunction handler, uint32_t duration, EventTearDownFunction tearDown)
    : _handler{handler},
      _duration(duration),
      _tearDown{tearDown},
      _startTime{rtc.now().secondstime()},
      _runned{false}
{
}

void Event::_run()
{
  _handler(rtc.now());
}

AbsoluteAlarm::AbsoluteAlarm(const DateTime &dateTime, EventHandlerFunction handler,
  uint32_t duration, EventTearDownFunction tearDown)
    : Event(handler, duration, tearDown),
      _dateTime{dateTime}
{
}

bool AbsoluteAlarm::isHappen() const
{
  if (_dateTime == rtc.now())
  {
    return true;
  }
  return false;
}

RecurringAlarm::RecurringAlarm(uint8_t daysOfWeek, uint8_t hour, uint8_t minute, uint8_t second,
  EventHandlerFunction handler, uint32_t duration, EventTearDownFunction tearDown)
    : Event(handler, duration, tearDown),
      _daysOfWeek{daysOfWeek},
      _hour{hour},
      _minute{minute},
      _second{second}
{
}

bool RecurringAlarm::isHappen() const
{
  DateTime now = rtc.now();

  if (now.hour() == _hour && now.minute() == _minute && now.second() == _second)
  {
    for (uint8_t day = 0; day < 7; day++)
    {
      if (now.dayOfTheWeek() == day && _daysOfWeek.test(day))
      {
        return true;
      }
    }
  }
  return false;
}

Interval::Interval(const TimeSpan &timeSpan, EventHandlerFunction handler, uint32_t duration,
  EventTearDownFunction tearDown)
    : Event(handler, duration, tearDown),
      _timeSpan{timeSpan},
      _prevTime(rtc.now())
{
}

bool Interval::isHappen() const
{
  if (_prevTime + _timeSpan == rtc.now())
  {
    return true;
  }
  return false;
}

void Interval::_run()
{
  _prevTime = rtc.now();
  _handler(_prevTime);
}
