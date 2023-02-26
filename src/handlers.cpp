#include "handlers.h"

#include <ArduinoJson.h>
#include <LittleFS.h>
#include <DS3231.h>

#include "Time.h"

static const char *tablesDir = "/tables/";
extern RTClib rtc;

void handleRedirect(AsyncWebServerRequest *request)
{
	if (!request->url().endsWith("/"))
	{
		request->redirect(request->url() + "/");
	}
}

void handleGetTable(AsyncWebServerRequest *request)
{
	File file = LittleFS.open((tablesDir + request->pathArg(0) + ".json").c_str(), "r");
	StaticJsonDocument<256> json;
	deserializeJson(json, file);
	file.close();

	request->send(200, "application/json", json.as<String>());
}

void handleGetTables(AsyncWebServerRequest *request)
{
	Dir root = LittleFS.openDir(tablesDir);
	StaticJsonDocument<256> json;

	for (String fileName; root.next();)
	{
		fileName = root.fileName();
		json.add(fileName.substring(0, fileName.indexOf(".")));
	}

	request->send(200, "application/json", json.as<String>());
}

void handlePostTables(AsyncWebServerRequest *request, JsonVariant &json)
{
	JsonArray array = json.as<JsonArray>();
	StaticJsonDocument<256> doc;

	String path = tablesDir;

	for (JsonArray::iterator it = array.begin(); it != array.end(); ++it)
	{
		if ((*it).containsKey("title"))
		{
			path += (*it)["title"].as<String>();
		}
		else if ((*it).containsKey("time"))
		{
			doc.add((*it)["time"].as<String>());
		}
	}

	path += ".json";

	File file;
	file = LittleFS.open(path.c_str(), "w");
	serializeJson(doc, file);
	file.close();

	request->send(200);
}

void handleGetTime(AsyncWebServerRequest *request)
{
	Time now = rtc.now();

	StaticJsonDocument<128> time;
	time.add(String(now));

	request->send(200, "application/json", time.as<String>());
}
