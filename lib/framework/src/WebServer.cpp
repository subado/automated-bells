#include <AsyncJson.h>
#include <Rtc.hpp>
#include <Shedule.hpp>
#include <WebServer.hpp>

WebServer::WebServer(uint16_t port) : _server(port)
{
  // Needed for simply write front-end
#if defined(ENABLE_CORS)
  DefaultHeaders::Instance().addHeader(PSTR("Access-Control-Allow-Origin"), PSTR("*"));
#endif
  addHandlers();
}

void WebServer::begin()
{
  _server.serveStatic("/", LittleFS, "/client/").setDefaultFile("index.html");
  _server.begin();
}

void WebServer::end()
{
  _server.end();
}

void WebServer::addHandlers()
{
  // Response contains json with table which name was passed as a uri parameter
  // ([A-Za-z0-9]{1,31}) is regex which define uri parameter format
  _server.on("^\\/tables\\/([A-Za-z0-9]{1,31})$", HTTP_GET,
    [](AsyncWebServerRequest *request)
    {
      File file = LittleFS.open(("/tables" + request->pathArg(0) + ".json").c_str(), "r");
      DynamicJsonDocument json(2048);
      deserializeJson(json, file);
      file.close();

      request->send(200, "application/json", json.as<String>());
    });

  // Response contains json with the names of all tables
  _server.on("/tables", HTTP_GET,
    [](AsyncWebServerRequest *request)
    {
      Dir root = LittleFS.openDir("/tables");
      DynamicJsonDocument json(1024);

      for (String fileName; root.next();)
      {
        fileName = root.fileName();
        json.add(fileName.substring(0, fileName.indexOf(".")));
      }

      request->send(200, "application/json", json.as<String>());
    });

  // Parse the form sent in json format
  // and save the file with the parsed table
  _server.addHandler(new AsyncCallbackJsonWebHandler("/tables",
    [](AsyncWebServerRequest *request, JsonVariant &json)
    {
      JsonArray array = json.as<JsonArray>();
      DynamicJsonDocument doc(2048);

      String path = "/tables";

      for (JsonVariant value : array)
      {
        if (value.containsKey("title"))
        {
          path += value["title"].as<String>();
        }
        else if (value.containsKey("time"))
        {
          doc.add(value["time"].as<String>());
        }
      }

      path += ".json";

      File file;
      file = LittleFS.open(path.c_str(), "w");
      serializeJson(doc, file);
      file.close();

      request->send(200);
    }));

  // Get the time from the rtc module and send json with it
  _server.on("/time", HTTP_GET,
    [](AsyncWebServerRequest *request)
    {
      DateTime now = rtc.now();

      StaticJsonDocument<32> time;
      time.add(now.timestamp(DateTime::TIMESTAMP_TIME));

      request->send(200, "application/json", time.as<String>());
    });

  // Get the name of the active shedule and send json with it
  _server.on("/shedule", HTTP_GET,
    [](AsyncWebServerRequest *request)
    {
      StaticJsonDocument<64> doc;

      doc.add(shedule.name());

      request->send(200, "application/json", doc.as<String>());
    });

  // Set the name of the active shedule
  _server.addHandler(new AsyncCallbackJsonWebHandler("/shedule",
    [](AsyncWebServerRequest *request, JsonVariant &json)
    {
      shedule.setup(json.as<String>());
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
