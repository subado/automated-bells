#pragma once

#include <ArduinoJson.h>

#include <tuple>
#include <utility>

#include <Ntp.hpp>
#include <macros.h>

template <typename... Pairs>
class Config
{
public:
  Config(const char *fileName, const Pairs &...objects);

  void save(JsonObject obj) const;
  void load(JsonObjectConst obj);

  bool saveFile();
  bool loadFile();

  const char *fileName();
  void setFileName(const char *fileName);

private:
  template <std::size_t... Indexes>
  void _saveObjects(JsonObject obj, std::index_sequence<Indexes...>) const;

  template <std::size_t... Indexes>
  void _loadObjects(JsonObjectConst obj, std::index_sequence<Indexes...>);

  std::tuple<Pairs...> _objects;
  char _fileName[MAX_FILENAME_LENGTH];
};

template <typename... Pairs>
bool serializeConfig(const Config<Pairs...> &config, Print &dest);

template <typename... Pairs>
bool deserializeConfig(Stream &src, Config<Pairs...> &config);

#include <Config.tpp>
