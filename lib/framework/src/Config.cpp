#include <Config.hpp>
#include <LittleFS.h>
#include <algorithm>

Config::Config(size_t capacity, const String &path, const JsonObject &obj)
    : json(capacity),
      _path{path},
      _defaultObj{obj}
{
  reset();
}

String Config::path() const
{
  return _path;
}

void Config::setPath(const String &path)
{
  _path = path;
}

bool Config::load()
{
  return load(_path);
}

bool Config::load(const String &path)
{
  File file = LittleFS.open(_path, "r");
  auto error = deserializeJson(json, file);
  file.close();
  if (error.code() == DeserializationError::Ok)
  {
    return true;
  }
  reset();
  return false;
}

bool Config::save() const
{
  return save(_path);
}

bool Config::save(const String &path) const
{
  File file = LittleFS.open(_path, "w");
  size_t bytes = serializeJson(json, file);
  file.close();
  if (bytes)
  {
    return true;
  }
  return false;
}

void Config::setDefaultObject(const JsonObject &obj)
{
  _defaultObj = obj;
}

void Config::reset()
{
  json.set(_defaultObj);
}
