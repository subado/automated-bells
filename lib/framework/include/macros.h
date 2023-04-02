#pragma once

#define MAX_FILENAME_LENGTH 32
#define TRACE(fmt, ...)     Serial.printf(fmt, ##__VA_ARGS__)
#define CONFIG_FILENAME     "config.json"
