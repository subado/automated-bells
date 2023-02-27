#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <Wire.h>

#include <SimpleFTPServer.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <DS3231.h>

#include <stdio.h>
#include <vector>

#include "wifi.h"
#include "Time.h"
#include "handlers.h"


AsyncWebServer server(80);
FtpServer ftp;
RTClib rtc;
String shedule = "";

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

	server
	.serveStatic("/", LittleFS, "/client/")
	.setDefaultFile("index.html");

	server.begin();
	Serial.println("Http server started");
}

void loop()
{
	ftp.handleFTP();
}
