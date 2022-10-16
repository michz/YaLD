#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#include <ArduinoJson.h>

#include "debug.h"

#include "credentials.h"
#include "mqtt.h"
#include "updateServer.h"


extern WiFiClient espClient;

void handleRootPath();
void handleGetData();
void handlePostData();

#endif
