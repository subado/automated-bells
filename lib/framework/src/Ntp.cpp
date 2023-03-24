#include <Ntp.hpp>

Ntp::Ntp()
    : _udp(),
      _servers{},
      _serverIndex{0},
      _serverIp{},
      _timeZone{},
      _localPort{}
{
}

bool Ntp::begin(const std::set<String> &servers, int8_t timeZone, uint8_t localPort)
{
  _timeZone = timeZone;
  _servers = servers;
  _localPort = localPort;
  return _udp.begin(_localPort);
}

uint32_t Ntp::getTime()
{
  while (_udp.parsePacket() > 0)
    ; // discard any previously received packets

  const char *serverName = std::next(_servers.begin(), _serverIndex++)->c_str();
  WiFi.hostByName(serverName, _serverIp);
  Serial.printf("Ntp: %s ( %s ) -> ", serverName, _serverIp.toString().c_str());
  if (_serverIndex == _servers.size())
  {
    _serverIndex = 0;
  }
  _sendPacket();
  // May not work once after 50 days due to overflow of millis()
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500)
  {
    int size = _udp.parsePacket();
    if (size >= PACKET_SIZE)
    {
      Serial.println("get response");
      _udp.read(_packetBuffer, PACKET_SIZE); // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 = (unsigned long)_packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)_packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)_packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)_packetBuffer[43];
      return secsSince1900 - 2208988800UL + _timeZone * 3600UL; // 3600UL == SECS_PER_HOUR
    }
  }
  Serial.println("no response");
  return 0; // return 0 if unable to get the time
}

void Ntp::setServers(const std::set<String> &servers)
{
  _servers = servers;
  _serverIndex = 0;
}

void Ntp::setTimezone(int8_t timeZone)
{
  _timeZone = timeZone;
}

std::set<String> Ntp::servers()
{
  return _servers;
}

int8_t Ntp::timeZone()
{
  return _timeZone;
}

// send an NTP request to the time server at the given address
void Ntp::_sendPacket()
{
  // set all bytes in the buffer to 0
  memset(_packetBuffer, 0, PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  _packetBuffer[0] = 0b11100011; // LI, Version, Mode
  _packetBuffer[1] = 0;          // Stratum, or type of clock
  _packetBuffer[2] = 6;          // Polling Interval
  _packetBuffer[3] = 0xEC;       // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  _packetBuffer[12] = 49;
  _packetBuffer[13] = 0x4E;
  _packetBuffer[14] = 49;
  _packetBuffer[15] = 52;
  // all NTP fielrtc.have been given values, now
  // you can send a packet requesting a timestamp:
  _udp.beginPacket(_serverIp, 123); // NTP requests are to port 123
  _udp.write(_packetBuffer, PACKET_SIZE);
  _udp.endPacket();
}

Ntp ntp;
