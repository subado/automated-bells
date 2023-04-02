#include <WiFiManager.hpp>

WiFiManager::Details::Details()
    : _ssid{},
      _psk{}
{
}

WiFiManager::Details::Details(const char *ssid, const char *psk)
{
  setSsid(ssid);
  setSsid(psk);
}

void WiFiManager::Details::setSsid(const char *ssid)
{
  std::strncpy(_ssid, ssid, sizeof(_ssid));
}

void WiFiManager::Details::setPsk(const char *psk)
{
  std::strncpy(_psk, psk, sizeof(_psk));
}

const char *WiFiManager::Details::ssid() const
{
  return _ssid;
}

const char *WiFiManager::Details::psk() const
{
  return _psk;
}

void WiFiManager::configAp(const IPAddress &apLocalIp, const IPAddress &apGateway,
  const IPAddress &apSubnet)
{
  _apLocalIp = apLocalIp;
  _apGateway = apGateway;
  _apSubnet = apSubnet;
}

bool WiFiManager::beginSta(int32_t channel, const uint8_t *bssid, bool connect) const
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(_sta.ssid(), _sta.psk(), channel, bssid, connect);
  Serial.print("Connecting");
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("WiFi failed!");
    return false;
  }
  Serial.printf("\nConnected to %s ( ip %s )\n", _sta.ssid(), WiFi.localIP().toString().c_str());
  return true;
}

bool WiFiManager::createAp(int channel, int ssid_hidden, int max_connection,
  int beacon_interval) const
{
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(_apLocalIp, _apGateway, _apSubnet);

  if (!WiFi.softAP(_ap.ssid(), _ap.psk(), channel, ssid_hidden, max_connection, beacon_interval))
  {
    Serial.println("Failed to create access point");
    return false;
  }

  Serial.printf("Access point created %s ( ip %s )\n", _ap.ssid(),
    WiFi.softAPIP().toString().c_str());
  return true;
}

void WiFiManager::setStaDetails(const Details &details)
{
  _sta = details;
}

void WiFiManager::setApDetails(const Details &details)
{
  _ap = details;
}

const WiFiManager::Details &WiFiManager::staDetails() const
{
  return _sta;
}

const WiFiManager::Details &WiFiManager::apDetails() const
{
  return _ap;
}

bool convertToJson(const WiFiManager::Details &src, JsonVariant dst)
{
  return dst["ssid"].set(src.ssid()) && dst["psk"].set(src.psk());
}

void convertFromJson(JsonVariantConst src, WiFiManager::Details &dst)
{
  dst.setSsid(src["ssid"].as<const char *>());
  dst.setPsk(src["psk"].as<const char *>());
}

bool canConvertFromJson(JsonVariantConst src, const WiFiManager::Details &)
{
  return src["ssid"].is<const char *>() && src["psk"].is<const char *>();
}

bool convertToJson(const WiFiManager &src, JsonVariant dst)
{
  return dst["sta"].set(src.staDetails()) && dst["ap"].set(src.apDetails());
}

void convertFromJson(JsonVariantConst src, WiFiManager &dst)
{
  dst.setStaDetails(src["sta"]);
  dst.setApDetails(src["ap"]);
}

bool canConvertFromJson(JsonVariantConst src, const WiFiManager &)
{
  return src["sta"].is<WiFiManager::Details>() && src["ap"].is<WiFiManager::Details>();
}

WiFiManager wifiManager;
