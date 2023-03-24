#include <Scheduler.hpp>

#include <ArduinoJson.h>
#include <Rtc.hpp>

#include <EventManager.hpp>

static uint8_t conv2d(const String &str)
{
  return 10 * (str[0] - '0') + str[1] - '0';
}

Scheduler::Scheduler()
    : _title{},
      _events{}
{
}

void Scheduler::setTable(const String &title)
{
  _clearEvents();
  File file = LittleFS.open(("/tables/" + title + ".json").c_str(), "r");
  _parseJson(file);
  file.close();

  _title = title;
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

String Scheduler::title()
{
  return _title;
}

void Scheduler::_parseJson(File &file)
{
  StaticJsonDocument<1024> json;
  deserializeJson(json, file);

  JsonArray array = json.as<JsonArray>();

  String time;
  for (JsonVariant value : array)
  {
    time = value.as<String>();
    _events.push_back(
      eventManager.setRecurringAlarm(RecurringAlarm::Days::EVERY, conv2d(time.substring(0, 2)),
        conv2d(time.substring(3, 5)), 0, _handler, _duration, _tearDown));
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
