#pragma once

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <vector>

#include <Rtc.hpp>

#define PACKET_SIZE 48 // NTP time is in the first 48 bytes of message

class Ntp
{
public:
  Ntp();
  Ntp(const Ntp &other);
  Ntp(const Ntp &&other);

  bool begin(uint8_t localPort = 123);
  bool begin(std::initializer_list<const char *> servers, int8_t timeZone = 0,
    uint8_t localPort = 123);

  void stop();

  void clearServers();
  void addServer(const char *server);
  void setServers(std::initializer_list<const char *> servers);

  void setTimezone(int8_t timeZone);

  const std::vector<String> &servers() const;
  int8_t timeZone() const;

  uint32_t getTime();
  bool syncTime(Rtc &rtc);

  Ntp &operator=(const Ntp &other);
  Ntp &operator=(const Ntp &&other);

private:
  void _sendPacket();

  WiFiUDP _udp; // NTP uses the UDP protocol for its work

  std::vector<String> _servers;
  std::size_t _serverIndex;
  IPAddress _serverIp;
  int8_t _timeZone; // 0 means UTC+0

  byte _packetBuffer[PACKET_SIZE]; // buffer to hold incoming & outgoing packets
};

bool convertToJson(const Ntp &src, JsonVariant dst);
void convertFromJson(JsonVariantConst src, Ntp &dst);
bool canConvertFromJson(JsonVariantConst src, const Ntp &);

extern Ntp ntp;
