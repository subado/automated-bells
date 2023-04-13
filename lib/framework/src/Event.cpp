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

bool Event::isSelfDestructive() const
{
  return false;
}

void Event::setHandler(EventHandlerFunction handler)
{
  _handler = handler;
}

void Event::setTearDown(EventTearDownFunction tearDown)
{
  _tearDown = tearDown;
}

void Event::setDuration(uint32_t duration)
{
  _duration = duration;
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

bool AbsoluteAlarm::isSelfDestructive() const
{
  return true;
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
  uint32_t timeSpan, uint32_t repeatsNum)
    : Event(handler, tearDown, duration),
      _timeSpan{timeSpan},
      _prevTime{},
      _repeatsNum{repeatsNum},
      _repeatsCounter{}
{
}

bool Interval::isHappen() const
{
  if (_prevTime.secondstime() + _timeSpan <= rtc.now().secondstime())
  {
    return true;
  }
  return false;
}

bool Interval::isSelfDestructive() const
{
  return _repeatsNum != 0 && _repeatsCounter == _repeatsNum;
}

void Interval::_run()
{
  ++_repeatsCounter;
  _prevTime = rtc.now();
  _handler(_prevTime);
}
