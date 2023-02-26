#ifndef HANDLERS_H
#define HANDLERS_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

void handleGetTables(AsyncWebServerRequest *request);
void handleRedirect(AsyncWebServerRequest *request);
void handlePostTables(AsyncWebServerRequest *request);
void handleGetTable(AsyncWebServerRequest *request);

#endif // HANDLERS_H
