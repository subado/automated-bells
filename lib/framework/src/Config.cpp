#include <Config.hpp>

#include <LittleFS.h>

Config::Config(Ntp &ntp, const char *fileName)
    : _ntp{ntp}
{
  setFileName(fileName);
}

void Config::save(JsonObject obj) const
{
  obj["ntp"] = _ntp;
}

void Config::load(JsonObjectConst obj)
{
  _ntp = obj["ntp"];
}

bool Config::saveFile()
{
  File file = LittleFS.open(_fileName, "w");
  if (!file)
  {
    Serial.println(F("Failed to create configuration file"));
    return false;
  }
  bool success = serializeConfig(config, file);
  file.close();
  if (!success)
  {
    Serial.println(F("Failed to serialize configuration"));
    return false;
  }
  return true;
}

bool Config::loadFile()
{
  File file = LittleFS.open(_fileName, "r");
  if (!file)
  {
    Serial.println(F("Failed to open config file"));
    return false;
  }
  bool success = deserializeConfig(file, config);
  file.close();
  if (!success)
  {
    Serial.println(F("Failed to deserialize configuration"));
    return false;
  }
  return true;
}

const char *Config::fileName()
{
  return _fileName;
}

void Config::setFileName(const char *fileName)
{
  std::strncpy(_fileName, fileName, sizeof(_fileName));
}

bool serializeConfig(const Config &config, Print &dest)
{
  DynamicJsonDocument doc(1024);

  JsonObject root = doc.to<JsonObject>();
  config.save(root);

  return serializeJson(doc, dest) > 0;
}

bool deserializeConfig(Stream &src, Config &config)
{
  DynamicJsonDocument doc(1024);
  DeserializationError err = deserializeJson(doc, src);
  if (err)
  {
    return false;
  }
  config.load(doc.as<JsonObject>());

  return true;
}
