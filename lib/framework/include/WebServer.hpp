#pragma once

#include <ESPAsyncWebServer.h>

class WebServer
{
public:
  WebServer(uint16_t port = 80);

  void begin(std::function<void()> saveConfig, std::function<void()> loadConfig);
  void end();

private:
  void _addHandlers();

  AsyncWebServer _server;
  std::function<void()> _saveConfig;
  std::function<void()> _loadConfig;
};

extern WebServer server;
