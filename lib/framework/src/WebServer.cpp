#include <WebServer.hpp>

#include <AsyncJson.h>
#include <Rtc.hpp>
#include <Scheduler.hpp>

#include <macros.h>
#include <utils.h>

WebServer::WebServer(uint16_t port)
    : _server(port)
{
  // Needed for simply write front-end
#if defined(ENABLE_CORS)
  DefaultHeaders::Instance().addHeader(PSTR("Access-Control-Allow-Origin"), PSTR("*"));
#endif
  _addHandlers();
}

void WebServer::begin()
{
  _server.serveStatic("/", LittleFS, "/static/").setDefaultFile("index.html");
  _server.begin();
}

void WebServer::end()
{
  _server.end();
}

void WebServer::_addHandlers()
{
  // Response contains json with table which name was passed as a uri parameter
  // ([A-Za-z0-9]{1,31}) is regex which define uri parameter format
  _server.on("^\\/api\\/tables\\/([A-Za-z0-9]{1,31})\\/$", HTTP_GET,
    [](AsyncWebServerRequest *request)
    {
      char path[MAX_FILENAME_LENGTH];
      const char *title = request->pathArg(0).c_str();
      utils::getPathToTable(path, title);
      if (LittleFS.exists(path))
      {
        File file = LittleFS.open(path, "r");

        DynamicJsonDocument json(2048);
        DynamicJsonDocument buffer(1024);

        deserializeJson(buffer, file);

        json["title"] = title;
        json["time"] = buffer;

        file.close();

        request->send(200, "application/json", json.as<String>());
      }
      request->send(404);
    });

  _server.on("^\\/api\\/tables\\/([A-Za-z0-9]{1,31})\\/$", HTTP_DELETE,
    [](AsyncWebServerRequest *request)
    {
      char path[MAX_FILENAME_LENGTH];
      utils::getPathToTable(path, request->pathArg(0).c_str());
      if (LittleFS.exists(path))
      {
        LittleFS.remove(path);
        request->send(200);
      }
      request->send(404);
    });

  // Response contains json with the names of all tables
  _server.on("/api/tables/", HTTP_GET,
    [](AsyncWebServerRequest *request)
    {
      Dir root = LittleFS.openDir("/tables");
      DynamicJsonDocument json(1024);
      JsonArray tables = json.createNestedArray("title");

      for (char fileName[MAX_FILENAME_LENGTH]; root.next();)
      {
        std::strncpy(fileName, root.fileName().c_str(), sizeof(fileName));
        utils::removeExtension(fileName);
        tables.add(fileName);
      }

      request->send(200, "application/json", json.as<String>());
    });

  // Parse the form sent in json format
  // and save the file with the parsed table
  _server.addHandler(new AsyncCallbackJsonWebHandler("/api/tables/",
    [](AsyncWebServerRequest *request, JsonVariant &data)
    {
      DynamicJsonDocument json(2048);

      json.set(data["time"].as<JsonArray>());
      char path[MAX_FILENAME_LENGTH];
      utils::getPathToTable(path, data["title"].as<const char *>());

      File file;
      file = LittleFS.open(path, "w");
      serializeJson(json, file);
      file.close();

      request->send(200);
    }));

  // Get the time from the rtc module and send json with it
  _server.on("/api/time/", HTTP_GET,
    [](AsyncWebServerRequest *request)
    {
      StaticJsonDocument<128> json;
      DateTime now = rtc.now();
      char buffer[3] = {0};

      std::snprintf(buffer, sizeof(buffer), "%02d", now.hour());
      json["hour"] = buffer;

      std::snprintf(buffer, sizeof(buffer), "%02d", now.minute());
      json["minute"] = buffer;

      std::snprintf(buffer, sizeof(buffer), "%02d", now.second());
      json["second"] = buffer;

      request->send(200, "application/json", json.as<String>());
    });

  // Get the name of the active scheduler and send json with it
  _server.on("/api/scheduler/", HTTP_GET,
    [](AsyncWebServerRequest *request)
    {
      StaticJsonDocument<64> json;

      json["title"] = scheduler.title();

      request->send(200, "application/json", json.as<String>());
    });

  // Set the name of the active scheduler
  _server.addHandler(new AsyncCallbackJsonWebHandler("/api/scheduler/",
    [](AsyncWebServerRequest *request, JsonVariant &json)

    {
      scheduler.setTable(json["title"].as<const char *>());
      request->send(200);
    }));

  // Redirect to url + '/', if nothing else wasn't work
  _server.on("^([^.]*[^/])$", HTTP_GET,
    [](AsyncWebServerRequest *request)
    {
      if (!request->url().endsWith("/"))
      {
        request->redirect(request->url() + "/");
      }
    });
}

WebServer server;
