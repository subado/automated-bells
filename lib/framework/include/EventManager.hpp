#pragma once

#include <RTClib.h>

#include <memory>

#include <Event.hpp>

class EventManager
{
public:
  template <typename T, typename... Args>
  Event *emplaceEvent(EventHandlerFunction handler, EventTearDownFunction tearDown,
    uint32_t duration, Args &&...args);

  template <typename T, typename... Args>
  Event *emplaceEvent(EventHandlerFunction handler, uint32_t duration, Args &&...args);

  void removeEvent(const Event *event);

  void handleEvents();

private:
  std::vector<std::unique_ptr<Event>> _events;
};

template <typename T, typename... Args>
Event *EventManager::emplaceEvent(EventHandlerFunction handler, EventTearDownFunction tearDown,
  uint32_t duration, Args &&...args)
{
  _events.emplace_back(
    std::make_unique<T>(handler, tearDown, duration, std::forward<Args>(args)...));
  return _events.back().get();
}

template <typename T, typename... Args>
Event *EventManager::emplaceEvent(EventHandlerFunction handler, uint32_t duration, Args &&...args)
{
  _events.emplace_back(std::make_unique<T>(
    handler, []() {}, duration, std::forward<Args>(args)...));
  return _events.back().get();
}

extern EventManager eventManager;
