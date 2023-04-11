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
    : _path{},
      _handler{},
      _tearDown{},
      _duration{},
      _events{}
{
}

void Scheduler::setEvents(const char *path)
{
  _clearEvents();
  File file = LittleFS.open(path, "r");
  _parseJson(file);
  file.close();

  std::strncpy(_path, path, sizeof(_path));
}

void Scheduler::setHandler(EventHandlerFunction handler)
{
  _handler = handler;
}

void Scheduler::setDuration(uint32_t duration)
{
  _duration = duration;
  for (auto event : _events)
  {
    event->setDuration(_duration);
  }
}

void Scheduler::setTearDown(EventTearDownFunction tearDown)
{
  _tearDown = tearDown;
}

const char *Scheduler::path() const
{
  return _path;
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
