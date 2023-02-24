#include <LittleFS.h>

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include <SimpleFTPServer.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <stdio.h>
#include <vector>

#include "configuration.h"
#include "ftpCallback.h"
#include "wifi.h"
#include "Time.h"
#include "handlers.h"

#define SSID "xxx"
#define PSK "xxx"

const char *jsonFile = "/bells.json";

AsyncWebServer server(80);
FtpServer ftp;

std::map<const char *,std::vector<Time>> table;

void setup()
{
	Serial.begin(9600);

	if (!LittleFS.begin())
	{
		Serial.println("Failed to mount file system");
		return;
	}
	Serial.println("Mount file system");

	const char *domainName = "bells";
	if (!wifiSta(SSID, PSK, domainName))
	{
		return;
	}
	
	MDNS.addService("http","tcp",80);

	ftp.setCallback(_callback);
	ftp.setTransferCallback(_transferCallback);
	ftp.begin(domainName, domainName);
	Serial.println("Ftp server started");
	Serial.printf("Login: %s\nPassword: %s\n", domainName, domainName);


	server.on("^([^.]*[^/])$", HTTP_GET, handleRedirect);
	server.on("/list/", HTTP_GET, handleList);

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
