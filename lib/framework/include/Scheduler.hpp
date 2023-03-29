#pragma once

#include <Arduino.h>
#include <LittleFS.h>

#include <ArduinoJson.h>

#include <vector>

#include <Event.hpp>
#include <Rtc.hpp>

class Scheduler
{
public:
  Scheduler();

  void setTable(const char *title);
  void setHandler(EventHandlerFunction handler);
  void setDuration(uint32_t duration);
  void setTearDown(EventTearDownFunction tearDown);

  const char *title() const;

private:
  void _parseJson(File &file);
  void _clearEvents();

  char _title[32];
  EventHandlerFunction _handler;
  uint32_t _duration;
  EventTearDownFunction _tearDown;
  std::vector<std::shared_ptr<Event>> _events;
};

extern Scheduler scheduler;
