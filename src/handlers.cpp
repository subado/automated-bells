#include "handlers.h"

#include <ArduinoJson.h>
#include <LittleFS.h>

void handleList(AsyncWebServerRequest *request)
{
	Dir root = LittleFS.openDir("/tables/");
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
