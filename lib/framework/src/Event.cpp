#include <Event.hpp>
#include <Rtc.hpp>

Event::Event(EventHandlerFunction handler) : _handler{handler}
{
}

void Event::_run()
{
  _handler(rtc.now());
}

AbsoluteAlarm::AbsoluteAlarm(const DateTime &dateTime, EventHandlerFunction handler)
    : Event(handler), _dateTime{dateTime}
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

RecurringAlarm::RecurringAlarm(uint8_t days, uint8_t hour, uint8_t minute, uint8_t second,
  EventHandlerFunction handler)
    : Event(handler), _days(days), _hour(hour), _minute(minute), _second(second)
{
}

bool RecurringAlarm::isHappen() const
{
  DateTime now = rtc.now();

  if (now.hour() == _hour && now.minute() == _minute && now.second() == _second)
  {
    for (uint8_t day = 0; day < 7; day++)
    {
      if (now.dayOfTheWeek() == day && _days.test(day))
      {
        return true;
      }
    }
  }
  return false;
}

Interval::Interval(const TimeSpan &timeSpan, EventHandlerFunction handler)
    : Event(handler), _timeSpan{timeSpan}, _prevTime(rtc.now())
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
