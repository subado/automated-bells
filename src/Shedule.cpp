#include "Shedule.h"

#include <ArduinoJson.h>

extern const char *tablesDir;

Shedule::Shedule()
: name_ {},
table_ {}
{
}

void Shedule::setup(const String &name)
{
	table_.clear();
	File file = LittleFS.open((tablesDir + name + ".json").c_str(), "r");
	parseJson(file);
	file.close();

	name_ = name;
}

String Shedule::name()
{
	return name_;
}

void Shedule::parseJson(File &file)
{
	DynamicJsonDocument json(2048);
	deserializeJson(json, file);
	
	JsonArray array = json.as<JsonArray>();

	for (JsonVariant value : array)
	{
		table_.push_back(static_cast<Time>(value.as<String>()));
	}
}
