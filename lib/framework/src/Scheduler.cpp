#include <Scheduler.hpp>

#include <ArduinoJson.h>
#include <Rtc.hpp>

#include <EventManager.hpp>
#include <macros.h>
#include <utils.h>

static uint8_t conv2d(const char *str)
{
  return 10 * (str[0] - '0') + str[1] - '0';
}

Scheduler::Scheduler()
    : _title{},
      _handler{},
      _tearDown{},
      _duration{},
      _events{}
{
}

void Scheduler::setTable(const char *title)
{
  _clearEvents();
  char path[MAX_FILENAME_LENGTH];
  utils::getPathToTable(path, title);
  File file = LittleFS.open(path, "r");
  _parseJson(file);
  file.close();

  std::strncpy(_title, title, sizeof(_title));
}

void Scheduler::setHandler(EventHandlerFunction handler)
{
  _handler = handler;
}

void Scheduler::setDuration(uint32_t duration)
{
  _duration = duration;
}

void Scheduler::setTearDown(EventTearDownFunction tearDown)
{
  _tearDown = tearDown;
}

const char *Scheduler::title() const
{
  return _title;
}

void Scheduler::_parseJson(File &file)
{
  DynamicJsonDocument json(2048);
  deserializeJson(json, file);

  JsonArray array = json.as<JsonArray>();
  const char *time;
  for (JsonVariant value : array)
  {
    time = value.as<const char *>();
    _events.emplace_back(eventManager.emplaceEvent<RecurringAlarm>(_handler, _tearDown, _duration,
      RecurringAlarm::Time(conv2d(time), conv2d(time + 3))));
  }
}

void Scheduler::_clearEvents()
{
  for (const auto &event : _events)
  {
    eventManager.removeEvent(event);
  }
  _events.clear();
}

Scheduler scheduler;
