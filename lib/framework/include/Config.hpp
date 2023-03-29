#pragma once

#include <ArduinoJson.h>

#include <Ntp.hpp>
#include <macros.h>

class Config
{
public:
  Config(Ntp &ntp, const char *fileName);

  void save(JsonObject obj) const;
  void load(JsonObjectConst obj);

  bool saveFile();
  bool loadFile();

  const char *fileName();
  void setFileName(const char *fileName);

private:
  Ntp &_ntp;
  char _fileName[MAX_FILENAME_LENGTH];
};

bool serializeConfig(const Config &config, Print &dest);
bool deserializeConfig(Stream &src, Config &config);

extern Config config;
