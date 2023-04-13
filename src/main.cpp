// built-in libraries in framework headers
#include <ESP8266WiFi.h>
#include <LittleFS.h>

// external libraries headers
#include <AsyncJson.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
// std c++ libraries headers
#include <utility>
#include <vector>

// my own headers
#include <Config.hpp>
#include <EventManager.hpp>
#include <Ntp.hpp>
#include <Rtc.hpp>
#include <Scheduler.hpp>
#include <WebServer.hpp>
#include <WiFiManager.hpp>

#define RTC_SDA 4
#define RTC_SCL 5

Config config(CONFIG_FILENAME, 1024, make_configurable("ntp", ntp),
  make_configurable("wifi", wifiManager), make_configurable("scheduler", scheduler));

void setup()
{
  Serial.begin(9600);

  if (!rtc.begin(RTC_SDA, RTC_SCL))
  {
    Serial.println("Couldn't find RTC\n");
    ESP.restart();
  }

  if (!LittleFS.begin())
  {
    Serial.println("Failed to mount file system");
    return;
  }
  Serial.println("Mount file system");

  scheduler.setHandler(
    [](uint8_t pin, const DateTime &dt)
    {
      digitalWrite(pin, HIGH);
      Serial.printf("XXXXXXXXX\n%s %s\n", "RING START!!!",
        dt.timestamp(DateTime::TIMESTAMP_TIME).c_str());
    });
  scheduler.setTearDown(
    [](uint8_t pin)
    {
      digitalWrite(pin, LOW);
      Serial.printf("%s %s\nXXXXXXXXX\n", "RING END!!!",
        rtc.now().timestamp(DateTime::TIMESTAMP_TIME).c_str());
    });

  config.loadFile();

  wifiManager.configAp(IPAddress(192, 168, 0, 4), IPAddress(192, 168, 0, 4),
    IPAddress(255, 255, 255, 0));
  wifiManager.begin();

  ntp.begin();

  eventManager.emplaceEvent<Interval>(
    [](const DateTime &dt)
    {
      if (ntp.syncTime(rtc))
      {
        Serial.printf("---\n%s %s\n---\n", "Sync time",
          rtc.now().timestamp(DateTime::TIMESTAMP_TIME).c_str());
      }
    },
    1, 1 * 60 * 60);

  server.begin(
    []()
    {
      config.saveFile();
    },
    []()
    {
      config.loadFile();
    });
  Serial.println("Http server started");
}

void loop()
{
  eventManager.handleEvents();
}
