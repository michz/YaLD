#include "main.h"


#define MZTX_FIRMWARE_VERSION "1"
#define WEBSERVER_DEFAUL_PORT 80

#define CHANNEL_COUNT 32

#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG

#define MZTX_DEBUG_INIT()            Serial.begin(115200)
#define MZTX_DEBUG_PRINT(msg)        Serial.print(msg)
#define MZTX_DEBUG_PRINTLN(msg)      Serial.println(msg)
#define MZTX_DEBUG_FORCEFLUSH()      Serial.flush()

#else

#define MZTX_DEBUG_INIT()
#define MZTX_DEBUG_PRINT(msg)
#define MZTX_DEBUG_PRINTLN(msg)
#define MZTX_DEBUG_FORCEFLUSH()

#endif


WiFiClient espClient;
WebServer server(WEBSERVER_DEFAUL_PORT);

uint8_t data[CHANNEL_COUNT];

/*
Topics:

/yald/1/rgb/1/set {r: 255, g: 0, b: 255}
/yald/1/channel/8/set 255

/yald/1/rgb/+/set {r: r, g: g, b: b}
/yald/1/channel/+/set value
*/

#define MQTT_TOPIC_BASE                     "/yald/"
#define MQTT_TOPIC_WILDCARD_SINGLE          "+"
#define MQTT_TOPIC_FORMAT_SINGLE            "%d"
#define MQTT_TOPIC_CHANNEL                  "/channel/"
#define MQTT_TOPIC_RGB                      "/rgb/"
#define MQTT_TOPIC_SET_SUFFIX               "/set"
#define MQTT_TOPIC_FIRMWARE_VERSION_SUFFIX  "/_firmware/version"

#define MQTT_TOPIC_SET_RGB                  MQTT_TOPIC_BASE MZTX_DEVICE_ID MQTT_TOPIC_RGB MQTT_TOPIC_WILDCARD_SINGLE MQTT_TOPIC_SET_SUFFIX
#define MQTT_TOPIC_SET_CHANNEL              MQTT_TOPIC_BASE MZTX_DEVICE_ID MQTT_TOPIC_CHANNEL MQTT_TOPIC_WILDCARD_SINGLE MQTT_TOPIC_SET_SUFFIX
#define MQTT_TOPIC_FORMAT_SET_RGB           MQTT_TOPIC_BASE MZTX_DEVICE_ID MQTT_TOPIC_RGB MQTT_TOPIC_FORMAT_SINGLE MQTT_TOPIC_SET_SUFFIX
#define MQTT_TOPIC_FORMAT_SET_CHANNEL       MQTT_TOPIC_BASE MZTX_DEVICE_ID MQTT_TOPIC_CHANNEL MQTT_TOPIC_FORMAT_SINGLE MQTT_TOPIC_SET_SUFFIX
#define MQTT_TOPIC_FIRMWARE_VERSION         MQTT_TOPIC_BASE MZTX_DEVICE_ID MQTT_TOPIC_FIRMWARE_VERSION_SUFFIX

void setup() {
    MZTX_DEBUG_INIT();

    // Init serial interface to LED processor
    Serial2.begin(38400, SERIAL_8N1);
    //Serial2.begin(19200, SERIAL_8N1, 12, 13);

    //WiFi.begin(WIFI_SSID, WIFI_KEY);

    // Init WIFI communication
    WiFi.persistent(false);             // Prevent flash corruption
    WiFi.setHostname(WIFI_HOSTNAME);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    WiFi.begin(WIFI_SSID, WIFI_KEY);

    while (WiFi.status() != WL_CONNECTED) {
        if (WiFi.status() == WL_CONNECT_FAILED) {
            //gotoSleep();
            MZTX_DEBUG_PRINTLN("WiFi setup failed. Waiting for 1s...");
            delay(1000);
        }

        MZTX_DEBUG_PRINTLN("WiFi not connected yet. Waiting for 250ms...");
        delay(250);
    }


    /*
    server.on("/healthz", []() {
        server.send(200, "text/plain", "OK");
    });

    server.on("/version", []() {
        server.send(200, "text/plain", MZTX_FIRMWARE_VERSION);
    });

    server.on("/data", HTTP_GET, handleGetData);
    server.on("/data", HTTP_POST, handlePostData);
    server.on("/", handleRootPath);
    */

    mqttInit();
    mqttReconnect();

    mqttSubscribe(MQTT_TOPIC_SET_RGB);
    mqttSubscribe(MQTT_TOPIC_SET_CHANNEL);

    mqttLoop();
    mqttPublish(MQTT_TOPIC_FIRMWARE_VERSION, MZTX_FIRMWARE_VERSION, true);

    server.begin();
}

inline void SendBreak()
{
    //s.end();

/*
    pinMode(17, OUTPUT);
    pinMatrixOutAttach(17, 0, false, false);
    digitalWrite(17, LOW);

    //delay(100);
    delayMicroseconds(573);
    //delayMicroseconds(1024);
*/
/*
    s.begin(300, SERIAL_8N1);       // open 300bps
    byte x[8];
    memset(x, 0x00, 8);
    s.write(x, 8);    // 500ms null(0) send => effect Send BREAK
    s.end();
*/

    //s.end();
    //s.begin(19200, SERIAL_8N1);     // reopen 19200bps

/*
    Serial2.end();
    pinMatrixOutDetach(17, false, false);
    pinMode(17, OUTPUT);
    pinMatrixOutAttach(17, 0, false, false);
    digitalWrite(17, LOW);

    delayMicroseconds(1);
    //delay(20);
    Serial2.begin(19200, SERIAL_8N1);

*/

    Serial2.updateBaudRate(9600);
    uint8_t buf[] = {0};
    Serial2.write(buf, sizeof(buf));
    Serial2.flush();
    Serial2.updateBaudRate(38400);

    //Serial2.end();

/*
    pinMode(17, OUTPUT);
    pinMatrixOutAttach(17, 0, false, false);
    digitalWrite(17, LOW);

    delayMicroseconds(573);
    pinMatrixOutAttach(17, UART_RXD_IDX(2), false, false);
    //Serial2.begin(19200, SERIAL_8N1);
*/

/*
    uartDetachTx(&_uart_bus_array[2]);
    pinMode(17, OUTPUT);
    digitalWrite(17, LOW);
    delayMicroseconds(573);
    uartAttachTx(&_uart_bus_array[2], 17, false);
*/
}

void loop() {
    // @TODO output repeatedly the current values in separate task / core
    //const uint8_t nullbytes[] = {0, 0, 0, 0, 0, 0, 0, 0};
    //MZTX_DEBUG_PRINTLN("loop");

    // break
    SendBreak();

/*
    for (int i = 0; i < CHANNEL_COUNT; ++i) {
        MZTX_DEBUG_PRINT(data[i]);
        MZTX_DEBUG_PRINT(',');
    }
    MZTX_DEBUG_PRINTLN();
*/

    //Serial2.write(data, 32);
    Serial2.write(data, CHANNEL_COUNT);
    Serial2.flush();
    /*

    //delay(50);

    //data[2] += 1;

    //server.handleClient();

    */
    if (false == mqttConnected()) {
        mqttReconnect();
    }

    mqttLoop();
}
/*
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
*/

void mqttCallback(char* topic, byte* payload, unsigned int length)
{
    int channel = 0;
    if (1 == sscanf(topic, MQTT_TOPIC_FORMAT_SET_RGB, &channel)) {
        MZTX_DEBUG_PRINTLN("RGB line");

        const int capacity = JSON_OBJECT_SIZE(12*4);
        StaticJsonDocument<capacity> doc;
        DeserializationError err = deserializeJson(doc, payload, length);

        if (err) {
            return;
        }

        data[channel-1] = (uint8_t) (doc["r"]);
        data[channel] = (uint8_t) (doc["g"]);
        data[channel+1] = (uint8_t) (doc["b"]);
    } else if (1 == sscanf(topic, MQTT_TOPIC_FORMAT_SET_CHANNEL, &channel)) {
        uint8_t s[32];
        strncpy((char*) s, (const char*) payload, min(length, (unsigned int) 32));
        uint8_t value = 0;
        value = atoi((const char *)s);
        data[channel-1] = value;
        MZTX_DEBUG_PRINTLN("Channel line");
        MZTX_DEBUG_PRINTLN(channel);
        MZTX_DEBUG_PRINTLN(value);
    }
}
