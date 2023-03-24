#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>

class WiFiManager
{
public:
  void config(const IPAddress &localIp, const IPAddress &gateway, const IPAddress &subnet);

  bool beginSta(const char *ssid, const char *passphrase = NULL, int32_t channel = 0,
    const uint8_t *bssid = NULL, bool connect = true) const;
  bool createAp(const char *ssid, const char *psk = NULL, int channel = 1, int ssid_hidden = 0,
    int max_connection = 4, int beacon_interval = 100) const;

private:
  IPAddress _localIp, _gateway, _subnet;
};

extern WiFiManager wifiManager;
