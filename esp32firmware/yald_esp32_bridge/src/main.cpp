#include "main.h"
#include "credentials.h"
#include "mqtt.h"

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#include <ArduinoJson.h>


#define MZTX_FIRMWARE_VERSION "1"
#define WEBSERVER_DEFAUL_PORT 80

#define CHANNEL_COUNT 32

WiFiClient espClient;
WebServer server(WEBSERVER_DEFAUL_PORT);

uint8_t data[CHANNEL_COUNT];

// basically: "yald/123/version"
char topicVersion[17];

// basically: "yald/123/setAll"
char topicSetAll[16];

// basically: "yald/123/set"
char topicSet[13];

// basically: "yald/123/state"
char topicState[15];


void setup() {
    // init topics
    snprintf(topicVersion, sizeof(topicVersion), "yald/%s/version", MZTX_DEVICE_ID);
    snprintf(topicSetAll, sizeof(topicSetAll), "yald/%s/setAll", MZTX_DEVICE_ID);
    snprintf(topicSet, sizeof(topicSet), "yald/%s/set", MZTX_DEVICE_ID);
    snprintf(topicState, sizeof(topicState), "yald/%s/state", MZTX_DEVICE_ID);

    Serial2.begin(19200, SERIAL_8N1);
    //Serial2.begin(19200, SERIAL_8N1, 12, 13);
    WiFi.begin(WIFI_SSID, WIFI_KEY);

    server.on("/healthz", []() {
        server.send(200, "text/plain", "OK");
    });

    server.on("/version", []() {
        server.send(200, "text/plain", MZTX_FIRMWARE_VERSION);
    });

    server.on("/data", HTTP_GET, handleGetData);
    server.on("/data", HTTP_POST, handlePostData);
    server.on("/", handleRootPath);

    server.begin();

}

inline void SendBreak(HardwareSerial s)
{
    s.end();

    pinMode(17, OUTPUT);
    pinMatrixOutAttach(17, 0, false, false);
    digitalWrite(17, LOW);

    delayMicroseconds(250);
/*
    s.begin(300, SERIAL_8N1);       // open 300bps
    byte x[8];
    memset(x, 0x00, 8);
    s.write(x, 8);    // 500ms null(0) send => effect Send BREAK
    s.end();
*/

    s.begin(19200, SERIAL_8N1);     // reopen 19200bps
}

void loop() {
    // @TODO output repeatedly the current values in separate task / core
    //const uint8_t nullbytes[] = {0, 0, 0, 0, 0, 0, 0, 0};

    // break
    SendBreak(Serial2);

    Serial2.write(data, CHANNEL_COUNT);
    Serial2.flush();

    //delay(50);

    //data[2] += 1;

    server.handleClient();

    if (false == mqttConnected()) {
        mqttReconnect();
    }

    mqttLoop();
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
        data[key] = (value & 0xFF);
    }

    server.send(200, "text/plain", "OK");
}

void mqttCallback(char* topic, byte* payload, unsigned int length)
{
    // @TODO
}
