#include <Event.hpp>
#include <Rtc.hpp>

Event::Event(EventHandlerFunction handler, EventTearDownFunction tearDown, uint32_t duration)
    : _handler{handler},
      _tearDown{tearDown},
      _duration(duration),
      _startTime{rtc.now().secondstime()},
      _runned{false}
{
}

void Event::_run()
{
  _handler(rtc.now());
}

AbsoluteAlarm::AbsoluteAlarm(EventHandlerFunction handler, EventTearDownFunction tearDown,
  uint32_t duration, const DateTime &dateTime)
    : Event(handler, tearDown, duration),
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

RecurringAlarm::Time::Time(uint8_t hour, uint8_t minute)
    : hour{hour},
      minute{minute},
      second{},
      daysOfWeek{Days::EVERY}
{
}

RecurringAlarm::Time::Time(uint8_t hour, uint8_t minute, uint8_t second, uint8_t daysOfWeek)
    : hour{hour},
      minute{minute},
      second{second},
      daysOfWeek{daysOfWeek}
{
}

RecurringAlarm::RecurringAlarm(EventHandlerFunction handler, EventTearDownFunction tearDown,
  uint32_t duration, const Time &time)
    : Event(handler, tearDown, duration),
      _time{time}
{
}

bool RecurringAlarm::isHappen() const
{
  DateTime now = rtc.now();

  if (now.hour() == _time.hour && now.minute() == _time.minute && now.second() == _time.second)
  {
    for (uint8_t day = 0; day < 7; day++)
    {
      if (now.dayOfTheWeek() == day && _time.daysOfWeek.test(day))
      {
        return true;
      }
    }
  }
  return false;
}

Interval::Interval(EventHandlerFunction handler, EventTearDownFunction tearDown, uint32_t duration,
  const TimeSpan &timeSpan)
    : Event(handler, tearDown, duration),
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
