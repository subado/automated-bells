#ifndef SHEDULE_H
#define SHEDULE_H

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

#endif // SHEDULE_H
