#include <Config.hpp>

#include <LittleFS.h>

template <typename... Pairs>
Config<Pairs...>::Config(const char *fileName, std::size_t capacity, const Pairs &...objects)
    : _capacity{capacity},
      _objects{objects...}
{
  setFileName(fileName);
}

template <typename... Pairs>
void Config<Pairs...>::save(JsonObject obj) const
{
  _saveObjects(obj, std::make_index_sequence<std::tuple_size_v<decltype(_objects)>>{});
}

template <typename... Pairs>
void Config<Pairs...>::load(JsonObjectConst obj)
{
  _loadObjects(obj, std::make_index_sequence<std::tuple_size_v<decltype(_objects)>>{});
}

template <typename... Pairs>
bool Config<Pairs...>::saveFile()
{
  File file = LittleFS.open(_fileName, "w");
  if (!file)
  {
    Serial.println(F("Failed to create configuration file"));
    return false;
  }
  bool success = serializeConfig(*this, file);
  file.close();
  if (!success)
  {
    Serial.println(F("Failed to serialize configuration"));
    return false;
  }
  return true;
}

template <typename... Pairs>
bool Config<Pairs...>::loadFile()
{
  File file = LittleFS.open(_fileName, "r");
  if (!file)
  {
    Serial.println(F("Failed to open config file"));
    return false;
  }
  bool success = deserializeConfig(file, *this);
  file.close();
  if (!success)
  {
    Serial.println(F("Failed to deserialize configuration"));
    return false;
  }
  return true;
}

template <typename... Pairs>
void Config<Pairs...>::setFileName(const char *fileName)
{
  std::strncpy(_fileName, fileName, sizeof(_fileName));
}

template <typename... Pairs>
void Config<Pairs...>::setCapacity(std::size_t capacity)
{
  _capacity = capacity;
}

template <typename... Pairs>
const char *Config<Pairs...>::fileName() const
{
  return _fileName;
}

template <typename... Pairs>
std::size_t Config<Pairs...>::capacity() const
{
  return _capacity;
}

template <typename... Pairs>
template <std::size_t... Indexes>
void Config<Pairs...>::_saveObjects(JsonObject obj, std::index_sequence<Indexes...>) const
{
  auto saveObject = [&obj](const auto &pair)
  {
    obj[pair.first] = pair.second;
  };

  (saveObject(std::get<Indexes>(_objects)), ...);
}

template <typename... Pairs>
template <std::size_t... Indexes>
void Config<Pairs...>::_loadObjects(JsonObjectConst obj, std::index_sequence<Indexes...>)
{
  auto loadObject = [&obj](const auto &pair)
  {
    pair.second = obj[pair.first];
  };

  (loadObject(std::get<Indexes>(_objects)), ...);
}

template <typename... Pairs>
bool serializeConfig(const Config<Pairs...> &config, Print &dest)
{
  DynamicJsonDocument doc(config.capacity());

  JsonObject root = doc.to<JsonObject>();
  config.save(root);

  return serializeJson(doc, dest) > 0;
}

template <typename... Pairs>
bool deserializeConfig(Stream &src, Config<Pairs...> &config)
{
  DynamicJsonDocument doc(config.capacity());
  DeserializationError err = deserializeJson(doc, src);
  if (err)
  {
    return false;
  }
  config.load(doc.as<JsonObject>());

  return true;
}
