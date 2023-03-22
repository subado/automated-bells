#pragma once

#include <Arduino.h>
#include <LittleFS.h>

#include <ArduinoJson.h>

#include <vector>

#include <Event.hpp>
#include <Rtc.hpp>

class Shedule
{
public:
  Shedule();

  void setTable(const String &title);
  void setHandler(EventHandlerFunction handler);
  void setDuration(uint32_t duration);
  void setTearDown(EventTearDownFunction tearDown);

  String title();

private:
  void _parseJson(File &file);
  void _clearEvents();

  String _title;
  EventHandlerFunction _handler;
  uint32_t _duration;
  EventTearDownFunction _tearDown;
  std::vector<std::shared_ptr<Event>> _events;
};

extern Shedule shedule;
