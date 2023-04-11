#pragma once

#include <Arduino.h>
#include <LittleFS.h>

#include <ArduinoJson.h>

#include <vector>

#include <Event.hpp>
#include <Rtc.hpp>
#include <macros.h>

class Scheduler
{
public:
  Scheduler();

  void setEvents(const char *path);
  void setHandler(EventHandlerFunction handler);
  void setTearDown(EventTearDownFunction tearDown);
  void setDuration(uint32_t duration);

  const char *path() const;

private:
  void _parseJson(File &file);
  void _clearEvents();

  char _path[MAX_FILENAME_LENGTH];
  EventHandlerFunction _handler;
  EventTearDownFunction _tearDown;
  uint32_t _duration;
  std::vector<const Event *> _events;
};

extern Scheduler scheduler;
