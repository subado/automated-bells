#pragma once

#include <Arduino.h>
#include <LittleFS.h>

#include <ArduinoJson.h>

#include <cstdint>
#include <vector>

#include <Event.hpp>
#include <Rtc.hpp>
#include <macros.h>

using SchedulerHandlerFunction = std::function<void(uint8_t pin, const DateTime &dateTime)>;
using SchedulerTearDownFunction = std::function<void(uint8_t pin)>;

class Scheduler
{
public:
  Scheduler();
  Scheduler(const Scheduler &other);

  void setTitle(const char *title);
  void setEvents();
  void setEvents(const char *title);
  void setHandler(SchedulerHandlerFunction handler);
  void setTearDown(SchedulerTearDownFunction tearDown);
  void setDuration(uint32_t duration);
  void setPin(uint8_t pin);

  const char *title() const;
  uint32_t duration() const;
  uint8_t pin() const;

  void clearEvents();

  Scheduler &operator=(const Scheduler &other);

private:
  void _parseJson(File &file);

  char _title[MAX_FILENAME_LENGTH];
  std::vector<Event *> _events;
  SchedulerHandlerFunction _handler;
  SchedulerTearDownFunction _tearDown;
  uint32_t _duration;
  uint8_t _pin;
};

bool convertToJson(const Scheduler &src, JsonVariant dst);
void convertFromJson(JsonVariantConst src, Scheduler &dst);
bool canConvertFromJson(JsonVariantConst src, const Scheduler &);

extern Scheduler scheduler;
