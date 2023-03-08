// built-in libraries in framework headers
#include <ESP8266WiFi.h>
#include <LittleFS.h>

// external libraries headers
#include <AsyncJson.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SimpleFTPServer.h>
// std c++ libraries headers
#include <stdio.h>
#include <vector>

// my own headers
#include <EventClock.hpp>
#include <Ntp.hpp>
#include <Rtc.hpp>
#include <Shedule.hpp>
#include <WebServer.hpp>
#include <WiFiManager.hpp>

#define APSSID  "bells"

#define RTC_SDA 4
#define RTC_SCL 5

FtpServer ftp;

void setup()
{
  Serial.begin(9600);

  if (!LittleFS.begin())
  {
    Serial.println("Failed to mount file system");
    return;
  }
  Serial.println("Mount file system");

  wifiManager.config(IPAddress(192, 168, 0, 177), IPAddress(192, 168, 0, 177),
    IPAddress(255, 255, 255, 0));
  if (!wifiManager.beginSta(SSID, PASS))
  {
    if (!wifiManager.createAp(APSSID))
      return;
  }

  const char *domainName = "bells";
  ftp.begin(domainName, domainName);
  Serial.println("Ftp server started");
  Serial.printf("Login: %s\nPassword: %s\n", domainName, domainName);

  server.begin();
  Serial.println("Http server started");

  if (!rtc.begin(RTC_SDA, RTC_SCL))
  {
    Serial.println("Couldn't find RTC");
  }
  ntp.begin(4, "2.pool.ntp.org");
  rtc.adjust(DateTime(ntp.getTime()));
  eventClock.setInterval(TimeSpan(60),
    [](const DateTime &dt)
    {
      rtc.adjust(DateTime(ntp.getTime()));
      Serial.printf("---\n%s %s\n---\n", "Sync time",
        rtc.now().timestamp(DateTime::TIMESTAMP_TIME).c_str());
    });
}

void loop()
{
  ftp.handleFTP();
  eventClock.handleEvents();
}
