#include <AsyncJson.h>
#include <Rtc.hpp>
#include <Scheduler.hpp>
#include <WebServer.hpp>

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
      String title = request->pathArg(0);
      String path = "/tables/" + title + ".json";
      if (LittleFS.exists(path))
      {
        File file = LittleFS.open(path, "r");

        StaticJsonDocument<2048> json, buffer;

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
      String title = request->pathArg(0);
      String path = "/tables/" + title + ".json";
      if (LittleFS.exists(path))
      {
        LittleFS.remove(path);
        request->send(200);
      }
      request->send(404);
    });

  // Response contains json with the names of all tables
  _server.on("^\\/api\\/tables\\/$", HTTP_GET,
    [](AsyncWebServerRequest *request)
    {
      Dir root = LittleFS.openDir("/tables");
      StaticJsonDocument<1024> json;
      JsonArray tables = json.createNestedArray("title");

      for (String fileName; root.next();)
      {
        fileName = root.fileName();
        tables.add(fileName.substring(0, fileName.indexOf(".")));
      }

      request->send(200, "application/json", json.as<String>());
    });

  // Parse the form sent in json format
  // and save the file with the parsed table
  _server.addHandler(new AsyncCallbackJsonWebHandler("/api/tables/",
    [](AsyncWebServerRequest *request, JsonVariant &data)
    {
      StaticJsonDocument<2048> json;

      String name = data["title"].as<String>();
      json.set(data["time"].as<JsonArray>());

      File file;
      file = LittleFS.open("/tables/" + name + ".json", "w");
      serializeJson(json, file);
      file.close();

      request->send(200);
    }));

  // Get the time from the rtc module and send json with it
  _server.on("^\\/api\\/time\\/$", HTTP_GET,
    [](AsyncWebServerRequest *request)
    {
      StaticJsonDocument<96> time;
      DateTime now = rtc.now();
      char buffer[4];

      sprintf(buffer, "%02d", now.hour());
      time["hour"] = String(buffer);
      sprintf(buffer, "%02d", now.minute());
      time["minute"] = String(buffer);
      sprintf(buffer, "%02d", now.second());
      time["second"] = String(buffer);

      request->send(200, "application/json", time.as<String>());
    });

  // Get the name of the active scheduler and send json with it
  _server.on("^\\/api\\/scheduler\\/$", HTTP_GET,
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
      scheduler.setTable(json["title"].as<String>());
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
