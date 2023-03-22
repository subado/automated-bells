// built-in libraries in framework headers
#include <ESP8266WiFi.h>
#include <LittleFS.h>

// external libraries headers
#include <AsyncJson.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
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

void setup()
{
  Serial.begin(9600);

  if (!LittleFS.begin())
  {
    Serial.println("Failed to mount file system");
    return;
  }
  Serial.println("Mount file system");

  wifiManager.config(IPAddress(192, 168, 0, 4), IPAddress(192, 168, 0, 4),
    IPAddress(255, 255, 255, 0));
  if (!wifiManager.beginSta(SSID, PASS))
  {
    if (!wifiManager.createAp(APSSID))
      return;
  }

  server.begin();
  Serial.println("Http server started");

  if (!rtc.begin(RTC_SDA, RTC_SCL))
  {
    Serial.println("Couldn't find RTC\n");
    ESP.restart();
  }
  ntp.begin(4, "2.pool.ntp.org");
  if (ntp.getTime())
  {
    rtc.adjust(DateTime(ntp.getTime()));
    eventClock.setInterval(TimeSpan(0, 1, 0, 0),
      [](const DateTime &dt)
      {
        if (ntp.getTime())
        {
          rtc.adjust(DateTime(ntp.getTime()));
          Serial.printf("---\n%s %s\n---\n", "Sync time",
            rtc.now().timestamp(DateTime::TIMESTAMP_TIME).c_str());
        }
      });
  }

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  shedule.setHandler(
    [](const DateTime &dt)
    {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.printf("XXXXXXXXX\n%s %s\n", "RING START!!!",
        dt.timestamp(DateTime::TIMESTAMP_TIME).c_str());
    });
  shedule.setDuration(5);
  shedule.setTearDown(
    []()
    {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.printf("%s %s\nXXXXXXXXX\n", "RING END!!!",
        rtc.now().timestamp(DateTime::TIMESTAMP_TIME).c_str());
    });
}

void loop()
{
  eventClock.handleEvents();
}
