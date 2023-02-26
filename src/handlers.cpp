#include "handlers.h"

#include <ArduinoJson.h>
#include <LittleFS.h>

static const char *tablesDir = "/tables/";

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

void handleRedirect(AsyncWebServerRequest *request)
{
	if (!request->url().endsWith("/"))
	{
		request->redirect(request->url() + "/");
	}
}

void handlePostTables(AsyncWebServerRequest *request)
{
	StaticJsonDocument<256> json;
	String path = tablesDir;

	size_t params = request->params();
	for (size_t i = 0; i < params; i++)
	{
		AsyncWebParameter* p = request->getParam(i);
		if (p->name() == "title")
		{
			path += p->value() + ".json";
		}
		else if (p->name() == "time")
		{
			json.add(p->value());
		}
	}

	File file;
	file = LittleFS.open(path.c_str(), "w");
	serializeJson(json, file);
	file.close();

	request->send(200);
}

void handleGetTable(AsyncWebServerRequest *request)
{
	File file = LittleFS.open((tablesDir + request->pathArg(0) + ".json").c_str(), "r");
	StaticJsonDocument<256> json;
	deserializeJson(json, file);
	file.close();

	request->send(200, "application/json", json.as<String>());
}
