#include "main.h"
#include "credentials.h"

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#include <ArduinoJson.h>

#define WEBSERVER_DEFAUL_PORT 80

#define CHANNEL_COUNT 32

WebServer server(WEBSERVER_DEFAUL_PORT);

uint8_t data[CHANNEL_COUNT];


void setup() {
    Serial.begin(19200);
    WiFi.begin(WIFI_SSID, WIFI_KEY);


    server.on("/healthz", []() {
        server.send(200, "text/plain", "OK");
    });

    server.on("/version", []() {
        server.send(200, "text/plain", "1.0.0");
    });

    server.on("/data", HTTP_GET, handleGetData);
    server.on("/data", HTTP_POST, handlePostData);
    server.on("/", handleRootPath);

    server.begin();

}

void loop() {
    // @TODO output repeatedly the current values

    server.handleClient();
}

void handleRootPath() {
    server.send(200, "text/plain", "See /data , /version , /healthz");
}

void handleGetData() {
    const int capacity = JSON_OBJECT_SIZE(CHANNEL_COUNT*4);
    StaticJsonDocument<capacity> doc;

    for (uint8_t i = 0; i < CHANNEL_COUNT; i++) {
        char key[5];
        sprintf(key, "%d", i);
        doc[key] = data[i];
    }

    char output[CHANNEL_COUNT*16];
    serializeJson(doc, output);
    server.send(200, "text/plain", output);
}

void handlePostData() {
    if (server.args() < 1) {
        server.send(400, "text/plain", "POST data missing");
        return;
    }

    const int capacity = JSON_OBJECT_SIZE(CHANNEL_COUNT*4);
    StaticJsonDocument<capacity> doc;
    DeserializationError err = deserializeJson(doc, server.arg(0));

    JsonObject object = doc.as<JsonObject>();

    if (err) {
        server.send(400, "text/plain", err.c_str());
        return;
    }

    for (JsonObject::iterator it=object.begin(); it!=object.end(); ++it) {
        uint8_t key = (uint8_t) atoi(it->key().c_str());
        uint8_t value = (uint8_t) it->value().as<int>();
        data[key] = value;
    }

    server.send(200, "text/plain", "OK");
}
