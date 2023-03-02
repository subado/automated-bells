#ifndef WIFI_HPP
#define WIFI_HPP

#include <Arduino.h>
#include <ESP8266WiFi.h>

bool wifiSta(const char *ssid, const char *psk, const char *hostname);
bool wifiAp(const char *ssid, const char *psk = "", const IPAddress &ip = IPAddress(192, 168, 0, 4));

#endif // WIFI_HPP
