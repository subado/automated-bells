#include <Shedule.hpp>

#include <ArduinoJson.h>
#include <Rtc.hpp>

Shedule::Shedule() : _title{}, _table{}
{
}

void Shedule::setup(const String &title)
{
  _table.clear();
  File file = LittleFS.open(("/tables" + title + ".json").c_str(), "r");
  parseJson(file);
  file.close();

  _title = title;
}

String Shedule::title()
{
  return _title;
}

void Shedule::parseJson(File &file)
{
  DynamicJsonDocument json(2048);
  deserializeJson(json, file);

  JsonArray array = json.as<JsonArray>();

  for (JsonVariant value : array)
  {
    _table.push_back(DateTime(
      (rtc.now().timestamp(DateTime::TIMESTAMP_DATE) + "T" + value.as<String>() + ":00").c_str()));
  }
}

Shedule shedule;
