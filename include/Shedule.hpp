#pragma once

#include <Arduino.h>
#include <LittleFS.h>

#include <ArduinoJson.h>

#include <vector>

#include "Time.hpp"

class Shedule
{
public:

	Shedule();

	void setup(const String &name);

	String name();

private:

	void parseJson(File &file);

	String name_;
	std::vector<Time> table_;

};
