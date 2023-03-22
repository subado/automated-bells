#include <Shedule.hpp>

#include <ArduinoJson.h>
#include <Rtc.hpp>

#include <EventClock.hpp>

static uint8_t conv2d(const String &str)
{
  return 10 * (str[0] - '0') + str[1] - '0';
}

Shedule::Shedule()
    : _title{},
      _events{}
{
}

void Shedule::setTable(const String &title)
{
  _clearEvents();
  File file = LittleFS.open(("/tables/" + title + ".json").c_str(), "r");
  _parseJson(file);
  file.close();

  _title = title;
}

void Shedule::setHandler(EventHandlerFunction handler)
{
  _handler = handler;
}

void Shedule::setDuration(uint32_t duration)
{
  _duration = duration;
}

void Shedule::setTearDown(EventTearDownFunction tearDown)
{
  _tearDown = tearDown;
}

String Shedule::title()
{
  return _title;
}

void Shedule::_parseJson(File &file)
{
  DynamicJsonDocument json(2048);
  deserializeJson(json, file);

  JsonArray array = json.as<JsonArray>();

  String time;
  for (JsonVariant value : array)
  {
    time = value.as<String>();
    _events.push_back(
      eventClock.setRecurringAlarm(RecurringAlarm::Days::EVERY, conv2d(time.substring(0, 2)),
        conv2d(time.substring(3, 5)), 0, _handler, _duration, _tearDown));
  }
}

void Shedule::_clearEvents()
{
  for (const auto &event : _events)
  {
    eventClock.removeEvent(event);
  }
  _events.clear();
}

Shedule shedule;
