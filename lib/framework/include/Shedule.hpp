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

  void setup(const String &title);

  String title();

private:
  void parseJson(File &file);

  String _title;
  std::vector<DateTime> _table;
};

extern Shedule shedule;
