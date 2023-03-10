#include <WiFiManager.hpp>

void WiFiManager::config(const IPAddress &localIp, const IPAddress &gateway,
  const IPAddress &subnet)
{
  _localIp = localIp;
  _gateway = gateway;
  _subnet = subnet;
}

bool WiFiManager::beginSta(const char *ssid, const char *passphrase, int32_t channel,
  const uint8_t *bssid, bool connect)
{
  WiFi.mode(WIFI_STA);
  // WiFi.config(_localIp, _gateway, _subnet);
  WiFi.begin(ssid, passphrase, channel, bssid, connect);
  Serial.print("Connecting");
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("WiFi failed!");
    return false;
  }
  Serial.printf("\nConnected to %s ( ip %s )\n", ssid, WiFi.localIP().toString().c_str());
  return true;
}

bool WiFiManager::createAp(const char *ssid, const char *psk, int channel, int ssid_hidden,
  int max_connection, int beacon_interval)
{
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(_localIp, _gateway, _subnet);

  if (!WiFi.softAP(ssid, psk, channel, ssid_hidden, max_connection, beacon_interval))
  {
    Serial.println("Failed to create access point");
    return false;
  }

  Serial.printf("Access point created %s ( ip %s )\n", ssid, WiFi.localIP().toString().c_str());
  return true;
}

WiFiManager wifiManager;
