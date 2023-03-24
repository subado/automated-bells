#pragma once

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <set>

#define PACKET_SIZE 48 // NTP time is in the first 48 bytes of message

class Ntp
{
public:
  Ntp();
  bool begin(const std::set<String> &servers, int8_t timeZone = 0, uint8_t localPort = 123);

  void setServers(const std::set<String> &servers);
  void setTimezone(int8_t timeZone);

  std::set<String> servers();
  int8_t timeZone();

  uint32_t getTime();

private:
  void _sendPacket();

  WiFiUDP _udp; // NTP uses the UDP protocol for its work

  std::set<String> _servers;
  size_t _serverIndex;
  IPAddress _serverIp;
  int8_t _timeZone;   // 0 means UTC+0
  uint8_t _localPort; // local port to listen for UDP packets

  byte _packetBuffer[PACKET_SIZE]; // buffer to hold incoming & outgoing packets
};

extern Ntp ntp;
