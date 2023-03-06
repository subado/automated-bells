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
#include <AlarmClock.hpp>
#include <AsyncWebServerHandlers.hpp>
#include <Rtc.hpp>
#include <Shedule.hpp>
#include <wifi.hpp>


#define RTC_SDA 12
#define RTC_SCL 14

const char *tablesDir = "/tables/";

AsyncWebServer server(80);
FtpServer ftp;
Shedule shedule;
Rtc rtc(RTC_SDA, RTC_SCL);
AlarmClock clocker;

void setup()
{
	Serial.begin(9600);

	if (!LittleFS.begin())
	{
		Serial.println("Failed to mount file system");
		return;
	}
	Serial.println("Mount file system");

	Wire.begin();

	const char *domainName = "bells";
	if (!wifiSta(SSID, PSK, domainName))
	{
		return;
	}

	ftp.begin(domainName, domainName);
	Serial.println("Ftp server started");
	Serial.printf("Login: %s\nPassword: %s\n", domainName, domainName);

	server.on("^\\/tables\\/([A-Za-z0-9]{1,31})$", HTTP_GET, handleGetTable);
	server.on("/tables", HTTP_GET, handleGetTables);

	server.addHandler(new AsyncCallbackJsonWebHandler("/tables", handlePostTables));

	server.on("/time", HTTP_GET, handleGetTime);

	server.on("/shedule", HTTP_GET, handleGetShedule);
	server.addHandler(new AsyncCallbackJsonWebHandler("/shedule", handlePostShedule));

	server.on("^([^.]*[^/])$", HTTP_GET, handleRedirect);

	server.serveStatic("/", LittleFS, "/client/").setDefaultFile("index.html");

	server.begin();
	Serial.println("Http server started");
	clocker.setInterval(TimeSpan(5), [](const DateTime &dt) {
		Serial.println("Interval 5 sec " + rtc.now().timestamp(DateTime::TIMESTAMP_TIME));
	});
	clocker.setAlarm(
		DateTime(rtc.now().toString("MMM DD YYYY"), "00:00:15"), [](const DateTime &dt) {
			Serial.println("Alarm 00:00:15 " + rtc.now().timestamp(DateTime::TIMESTAMP_TIME));
		});
	Serial.println(rtc.now().toString("DDD, DD MMM YYYY hh:mm:ss"));
}

void loop()
{
	ftp.handleFTP();
	clocker.handleEvents();
}
