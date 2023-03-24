#pragma once

#include <RTClib.h>
#include <functional>

#include <bitset>

class EventManager;
typedef std::function<void(const DateTime &dateTime)> EventHandlerFunction;
typedef std::function<void()> EventTearDownFunction;

class Event
{
public:
  Event(EventHandlerFunction handler, uint32_t duration, EventTearDownFunction tearDown);
  virtual ~Event() = default;

  virtual bool isHappen() const = 0;

protected:
  virtual void _run();

  EventHandlerFunction _handler;
  uint32_t _duration;
  EventTearDownFunction _tearDown;

  uint32_t _startTime;
  bool _runned;

  friend class EventManager;
};

class AbsoluteAlarm : public Event
{
public:
  AbsoluteAlarm(const DateTime &dateTime, EventHandlerFunction handler, uint32_t duration,
    EventTearDownFunction tearDown);

  bool isHappen() const override;

protected:
  DateTime _dateTime;
};

class RecurringAlarm : public Event
{
public:
  RecurringAlarm(uint8_t daysOfWeek, uint8_t hour, uint8_t minute, uint8_t second,
    EventHandlerFunction handler, uint32_t duration, EventTearDownFunction tearDown);

  bool isHappen() const override;

  enum Days
  {
    SUNDAY = 0b0000001,
    MONDAY = 0b0000010,
    TUESDAY = 0b0000100,
    WEDNESDAY = 0b0001000,
    THURSDAY = 0b0010000,
    FRIDAY = 0b0100000,
    SATURDAY = 0b1000000,
    EVERY = 0b1111111
  };

protected:
  std::bitset<7> _daysOfWeek;
  uint8_t _hour;
  uint8_t _minute;
  uint8_t _second;
};

class Interval : public Event
{
public:
  Interval(const TimeSpan &timeSpan, EventHandlerFunction handler, uint32_t duration,
    EventTearDownFunction tearDown);

  bool isHappen() const override;

protected:
  void _run() override;

  TimeSpan _timeSpan;
  DateTime _prevTime;
};
