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
  Config(const char *fileName, std::size_t capacity, const Pairs &...objects);

  void save(JsonObject obj) const;
  void load(JsonObjectConst obj);

  bool saveFile();
  bool loadFile();

  void setFileName(const char *fileName);
  void setCapacity(std::size_t capacity);

  const char *fileName() const;
  std::size_t capacity() const;

private:
  template <std::size_t... Indexes>
  void _saveObjects(JsonObject obj, std::index_sequence<Indexes...>) const;

  template <std::size_t... Indexes>
  void _loadObjects(JsonObjectConst obj, std::index_sequence<Indexes...>);

  char _fileName[MAX_FILENAME_LENGTH];
  std::size_t _capacity;
  std::tuple<Pairs...> _objects;
};

template <typename... Pairs>
bool serializeConfig(const Config<Pairs...> &config, Print &dest);

template <typename... Pairs>
bool deserializeConfig(Stream &src, Config<Pairs...> &config);

template <typename T>
std::pair<const char *, T &> make_configurable(const char *name, T &configurable);

#include <Config.tpp>
