#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

void handleRedirect(AsyncWebServerRequest *request);

void handleGetTable(AsyncWebServerRequest *request);
void handleGetTables(AsyncWebServerRequest *request);
void handlePostTables(AsyncWebServerRequest *request, JsonVariant &json);

void handleGetTime(AsyncWebServerRequest *request);

void handleGetShedule(AsyncWebServerRequest *request);
void handlePostShedule(AsyncWebServerRequest *request, JsonVariant &json);
