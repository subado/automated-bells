#include "handlers.hpp"

#include <ArduinoJson.h>
#include <LittleFS.h>
#include <DS3231.h>

#include "Time.hpp"
#include "Shedule.hpp"

extern const char *tablesDir;
extern RTClib rtc;
extern Shedule shedule;

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
	DynamicJsonDocument json(2048);
	deserializeJson(json, file);
	file.close();

	request->send(200, "application/json", json.as<String>());
}

void handleGetTables(AsyncWebServerRequest *request)
{
	Dir root = LittleFS.openDir(tablesDir);
	DynamicJsonDocument json(1024);

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
	DynamicJsonDocument doc(2048);

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
	Time now = RTClib::now();

	StaticJsonDocument<32> time;
	time.add(String(now));

	request->send(200, "application/json", time.as<String>());
}

void handleGetShedule(AsyncWebServerRequest *request)
{
	StaticJsonDocument<64> doc;

	doc.add(shedule.name());

	request->send(200, "application/json", doc.as<String>());
}

void handlePostShedule(AsyncWebServerRequest *request, JsonVariant &json)
{
	shedule.setup(json.as<String>());
	request->send(200);
}
