#ifndef HANDLERS_H
#define HANDLERS_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

void handleList(AsyncWebServerRequest *request);
void handleRedirect(AsyncWebServerRequest *request);

#endif // HANDLERS_H
