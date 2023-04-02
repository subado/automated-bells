#pragma once

#define MAX_FILENAME_LENGTH 32
#define MAX_SSID_LENGTH     32
#define MAX_PSK_LENGTH      64
#define TRACE(fmt, ...)     Serial.printf(fmt, ##__VA_ARGS__)
#define CONFIG_FILENAME     "config.json"
