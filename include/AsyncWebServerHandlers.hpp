#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

void handleRedirect(AsyncWebServerRequest *request);

void handleGetTable(AsyncWebServerRequest *request);
void handleGetTables(AsyncWebServerRequest *request);
void handlePostTables(AsyncWebServerRequest *request, JsonVariant &json);

void handleGetTime(AsyncWebServerRequest *request);

void handleGetShedule(AsyncWebServerRequest *request);
void handlePostShedule(AsyncWebServerRequest *request, JsonVariant &json);

#endif // HANDLERS_HPP
