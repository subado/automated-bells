#pragma once

#include <RTClib.h>
#include <functional>

#include <bitset>

class EventManager;
using EventHandlerFunction = std::function<void(const DateTime &dateTime)>;
using EventTearDownFunction = std::function<void()>;

class Event
{
public:
  Event(EventHandlerFunction handler, EventTearDownFunction tearDown, uint32_t duration);
  virtual ~Event() = default;

  virtual bool isHappen() const = 0;
  virtual bool isSelfDestructive() const;

  void setHandler(EventHandlerFunction handler);
  void setTearDown(EventTearDownFunction tearDown);
  void setDuration(uint32_t duration);

protected:
  virtual void _run();

  EventHandlerFunction _handler;
  EventTearDownFunction _tearDown;
  uint32_t _duration;

  uint32_t _startTime;
  bool _runned;

  friend class EventManager;
};

class AbsoluteAlarm : public Event
{
public:
  AbsoluteAlarm(EventHandlerFunction handler, EventTearDownFunction tearDown, uint32_t duration,
    const DateTime &dateTime);

  bool isHappen() const override;
  bool isSelfDestructive() const override;

protected:
  DateTime _dateTime;
};

class RecurringAlarm : public Event
{
public:
  class Time
  {
  public:
    Time(uint8_t hour, uint8_t minute);
    Time(uint8_t hour, uint8_t minute, uint8_t second, uint8_t daysOfWeek = Days::EVERY);

    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    std::bitset<7> daysOfWeek;
  };

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

  RecurringAlarm(EventHandlerFunction handler, EventTearDownFunction tearDown, uint32_t duration,
    const Time &time);

  bool isHappen() const override;

protected:
  Time _time;
};

class Interval : public Event
{
public:
  Interval(EventHandlerFunction handler, EventTearDownFunction tearDown, uint32_t duration,
    uint32_t timeSpan, uint32_t repeatsNum = 0);

  bool isHappen() const override;
  bool isSelfDestructive() const override;

protected:
  void _run() override;

  uint32_t _timeSpan;
  DateTime _prevTime;
  uint32_t _repeatsNum;
  uint32_t _repeatsCounter;
};
