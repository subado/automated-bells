#include <LittleFS.h>

#include <ESP8266WiFi.h>

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
	
	ftp.setCallback(_callback);
	ftp.setTransferCallback(_transferCallback);
	ftp.begin(domainName, domainName);
	Serial.println("Ftp server started");
	Serial.printf("Login: %s\nPassword: %s\n", domainName, domainName);

	server.on("^\\/tables\\/([A-Za-z0-9]+)$", HTTP_GET, handleGetTable);
	server.on("/tables", HTTP_POST, handlePostTables);
	server.on("/tables", HTTP_GET, handleGetTables);

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
