#pragma once

#include <ESPAsyncWebServer.h>

class WebServer
{
public:
  WebServer(uint16_t port = 80);

  void begin();
  void end();

private:
  void addHandlers();

  AsyncWebServer _server;
};

extern WebServer server;
