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
      _events{},
      _handler{},
      _tearDown{},
      _duration{},
      _pin{}
{
}

Scheduler::Scheduler(const Scheduler &other)
    : _title{},
      _events{},
      _handler{},
      _tearDown{},
      _duration{other._duration},
      _pin{other._pin}

{
  setEvents(other._title);
}

void Scheduler::setTitle(const char *title)
{
  std::strncpy(_title, title, sizeof(_title));
}

void Scheduler::setEvents()
{
  setEvents(_title);
}

void Scheduler::setEvents(const char *title)
{
  clearEvents();
  char path[MAX_FILENAME_LENGTH]{};
  utils::getPathToTable(path, title);
  File file = LittleFS.open(path, "r");
  _parseJson(file);
  file.close();

  setTitle(title);
}

void Scheduler::setHandler(SchedulerHandlerFunction handler)
{
  _handler = handler;
}

void Scheduler::setTearDown(SchedulerTearDownFunction tearDown)
{
  _tearDown = tearDown;
}

void Scheduler::setDuration(uint32_t duration)
{
  _duration = duration;
  for (auto event : _events)
  {
    event->setDuration(_duration);
  }
}

void Scheduler::setPin(uint8_t pin)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);
}
const char *Scheduler::title() const
{
  return _title;
}

uint32_t Scheduler::duration() const
{
  return _duration;
}

uint8_t Scheduler::pin() const
{
  return _pin;
}

void Scheduler::clearEvents()
{
  for (const auto &event : _events)
  {
    eventManager.removeEvent(event);
  }
  _events.clear();
}

Scheduler &Scheduler::operator=(const Scheduler &other)
{
  setEvents(other._title);
  _duration = other._duration;
  _pin = other._pin;

  return *this;
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
    _events.emplace_back(eventManager.emplaceEvent<RecurringAlarm>(
      std::bind(_handler, _pin, std::placeholders::_1), std::bind(_tearDown, _pin), _duration,
      RecurringAlarm::Time(conv2d(time), conv2d(time + 3))));
  }
}

bool convertToJson(const Scheduler &src, JsonVariant dst)
{
  return dst["duration"].set(src.duration()) && dst["pin"].set(src.pin()) &&
         dst["title"].set(src.title());
}

void convertFromJson(JsonVariantConst src, Scheduler &dst)
{
  dst.setDuration(src["duration"].as<uint32_t>());
  dst.setPin(src["pin"].as<uint8_t>());
  dst.setTitle(src["title"].as<const char *>());
}

bool canConvertFromJson(JsonVariantConst src, const Scheduler &)
{
  return src["duration"].is<uint32_t>() && src["pin"].is<uint8_t>() &&
         src["title"].is<const char *>();
}

Scheduler scheduler;
