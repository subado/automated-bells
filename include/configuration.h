#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <vector>

#include "Time.h"

void saveConfiguration(const char *filename, const std::vector<Time> &vec);
void loadConfiguration(const char *filename, std::vector<Time> &vec);

#endif // CONFIG_H
