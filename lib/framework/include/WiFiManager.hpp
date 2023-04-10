#pragma once

#include <ESP8266WiFi.h>

#include <ArduinoJson.h>

#include <macros.h>

class WiFiManager
{
public:
  class Details
  {
  public:
    Details();
    Details(const char *ssid, const char *psk);

    void setSsid(const char *ssid);
    void setPsk(const char *psk);

    const char *ssid() const;
    const char *psk() const;

  private:
    char _ssid[MAX_SSID_LENGTH];
    char _psk[MAX_PSK_LENGTH];
  };
  void configAp(const IPAddress &apLocalIp, const IPAddress &apGateway, const IPAddress &apSubnet);

  bool begin();
  bool beginSta(int32_t channel = 0, const uint8_t *bssid = NULL, bool connect = true) const;
  bool createAp(int channel = 1, int ssid_hidden = 0, int max_connection = 4,
    int beacon_interval = 100) const;

  void setStaDetails(const Details &details);
  void setApDetails(const Details &details);

  const Details &staDetails() const;
  const Details &apDetails() const;

private:
  Details _ap, _sta;

  IPAddress _apLocalIp, _apGateway, _apSubnet;
};

bool convertToJson(const WiFiManager::Details &src, JsonVariant dst);
void convertFromJson(JsonVariantConst src, WiFiManager::Details &dst);
bool canConvertFromJson(JsonVariantConst src, const WiFiManager::Details &);

bool convertToJson(const WiFiManager &src, JsonVariant dst);
void convertFromJson(JsonVariantConst src, WiFiManager &dst);
bool canConvertFromJson(JsonVariantConst src, const WiFiManager &);

extern WiFiManager wifiManager;
