#ifndef HANDLERS_H
#define HANDLERS_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

void handleRedirect(AsyncWebServerRequest *request);

void handleGetTable(AsyncWebServerRequest *request);
void handleGetTables(AsyncWebServerRequest *request);
void handlePostTables(AsyncWebServerRequest *request, JsonVariant &json);

void handleGetTime(AsyncWebServerRequest *request);

#endif // HANDLERS_H
