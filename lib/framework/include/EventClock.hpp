#pragma once

#include <RTClib.h>

#include <memory>

#include <Event.hpp>

#define DEFAULT_DURATION 1

class EventClock
{
public:
  std::shared_ptr<Event> setAbsoluteAlarm(
    const DateTime &dateTime, EventHandlerFunction handler, uint32_t duration = DEFAULT_DURATION,
    EventTearDownFunction tearDown = []() {});

  std::shared_ptr<Event> setRecurringAlarm(
    uint8_t days, uint8_t hour, uint8_t minute, uint8_t second, EventHandlerFunction handler,
    uint32_t duration = DEFAULT_DURATION, EventTearDownFunction tearDown = []() {});

  std::shared_ptr<Event> setInterval(
    const TimeSpan &timeSpan, EventHandlerFunction handler, uint32_t duration = DEFAULT_DURATION,
    EventTearDownFunction tearDown = []() {});

  void removeEvent(const std::shared_ptr<Event> &event);

  void handleEvents();

private:
  std::shared_ptr<Event> _addEvent(const std::shared_ptr<Event> &event);

  std::vector<std::shared_ptr<Event>> _events;
};

extern EventClock eventClock;
