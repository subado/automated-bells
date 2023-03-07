#include <Shedule.hpp>

#include <ArduinoJson.h>

extern const char *tablesDir;
extern Rtc rtc;

Shedule::Shedule() : _name{}, _table{}
{
}

void Shedule::setup(const String &name)
{
	_table.clear();
	File file = LittleFS.open((tablesDir + name + ".json").c_str(), "r");
	parseJson(file);
	file.close();

	_name = name;
}

String Shedule::name()
{
	return _name;
}

void Shedule::parseJson(File &file)
{
	DynamicJsonDocument json(2048);
	deserializeJson(json, file);

	JsonArray array = json.as<JsonArray>();

	for (JsonVariant value : array)
	{
		_table.push_back(DateTime(
			(rtc.now().timestamp(DateTime::TIMESTAMP_DATE) + "T" + value.as<String>() + ":00")
				.c_str()));
	}
}
