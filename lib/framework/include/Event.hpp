#pragma once

#include <RTClib.h>
#include <functional>

#include <bitset>

class EventClock;
typedef std::function<void(const DateTime &dateTime)> EventHandlerFunction;

class Event
{
public:
  Event(EventHandlerFunction handler);
  virtual ~Event() = default;

  virtual bool isHappen() const = 0;

protected:
  virtual void _run();

  EventHandlerFunction _handler;
  uint32_t _startTime;
  bool _runned = false;

  friend class EventClock;
};

class AbsoluteAlarm : public Event
{
public:
  AbsoluteAlarm(const DateTime &dateTime, EventHandlerFunction handler);

  bool isHappen() const override;

protected:
  DateTime _dateTime;
};

class RecurringAlarm : public Event
{
public:
  RecurringAlarm(uint8_t days, uint8_t hour, uint8_t minute, uint8_t second,
    EventHandlerFunction handler);

  bool isHappen() const override;

  enum Day
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
  std::bitset<7> _days;
  uint8_t _hour;
  uint8_t _minute;
  uint8_t _second;
};

class Interval : public Event
{
public:
  Interval(const TimeSpan &timeSpan, EventHandlerFunction handler);

  bool isHappen() const override;

protected:
  void _run() override;

  TimeSpan _timeSpan;
  DateTime _prevTime;
};
