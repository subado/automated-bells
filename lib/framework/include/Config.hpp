#pragma once

#include <ArduinoJson.h>
#include <set>

class Config
{
public:
  Config(size_t capacity, const String &path = "", const JsonObject &obj = {});

  String path() const;
  void setPath(const String &path);

  bool load();
  bool load(const String &path);

  bool save() const;
  bool save(const String &path) const;

  void setDefaultObject(const JsonObject &obj);

  void reset();

  DynamicJsonDocument json;

private:
  String _path;
  JsonObject _defaultObj;
};

extern Config config;
