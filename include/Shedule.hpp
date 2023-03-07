#pragma once

#include <Arduino.h>
#include <LittleFS.h>

#include <ArduinoJson.h>

#include <vector>

#include <Rtc.hpp>

class Shedule
{
public:
	Shedule();

	void setup(const String &name);

	String name();

private:
	void parseJson(File &file);

	String _name;
	std::vector<DateTime> _table;
};
