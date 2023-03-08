#pragma once

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define PACKET_SIZE 48 // NTP time is in the first 48 bytes of message

class Ntp
{
public:
  bool begin(int timeZone = 0, const char *serverName = "ru.pool.ntp.org", uint8_t localPort = 123);

  uint32_t getTime();

private:
  void sendPacket();

  WiFiUDP _udp; // NTP uses the UDP protocol for its work

  int _timeZone; // 0 means UTC+0
  const char *_serverName;
  IPAddress _serverIp; // NTP server's ip address
  uint8_t _localPort;  // local port to listen for UDP packets

  byte _packetBuffer[PACKET_SIZE]; // buffer to hold incoming & outgoing packets
};

extern Ntp ntp;
