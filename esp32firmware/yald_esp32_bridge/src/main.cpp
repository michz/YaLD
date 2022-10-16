#include "main.h"

#define CHANNEL_COUNT 32

WiFiClient espClient;
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
#define MQTT_TOPIC_MY_IP_SUFFIX             "/_my_ip"

#define MQTT_TOPIC_SET_RGB                  MQTT_TOPIC_BASE MZTX_DEVICE_ID MQTT_TOPIC_RGB MQTT_TOPIC_WILDCARD_SINGLE MQTT_TOPIC_SET_SUFFIX
#define MQTT_TOPIC_SET_CHANNEL              MQTT_TOPIC_BASE MZTX_DEVICE_ID MQTT_TOPIC_CHANNEL MQTT_TOPIC_WILDCARD_SINGLE MQTT_TOPIC_SET_SUFFIX
#define MQTT_TOPIC_FORMAT_SET_RGB           MQTT_TOPIC_BASE MZTX_DEVICE_ID MQTT_TOPIC_RGB MQTT_TOPIC_FORMAT_SINGLE MQTT_TOPIC_SET_SUFFIX
#define MQTT_TOPIC_FORMAT_SET_CHANNEL       MQTT_TOPIC_BASE MZTX_DEVICE_ID MQTT_TOPIC_CHANNEL MQTT_TOPIC_FORMAT_SINGLE MQTT_TOPIC_SET_SUFFIX
#define MQTT_TOPIC_FIRMWARE_VERSION         MQTT_TOPIC_BASE MZTX_DEVICE_ID MQTT_TOPIC_FIRMWARE_VERSION_SUFFIX
#define MQTT_TOPIC_MY_IP                    MQTT_TOPIC_BASE MZTX_DEVICE_ID MQTT_TOPIC_MY_IP_SUFFIX

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

    // Initialize data array (should be done automatically, but for sure...)
    memset(data, CHANNEL_COUNT, CHANNEL_COUNT * sizeof(uint8_t));

   initUpdateServer();

    mqttInit();
    mqttReconnect();

    mqttSubscribe(MQTT_TOPIC_SET_RGB);
    mqttSubscribe(MQTT_TOPIC_SET_CHANNEL);

    mqttLoop();
    mqttPublish(MQTT_TOPIC_FIRMWARE_VERSION, MZTX_FIRMWARE_VERSION, true);
    mqttPublish(MQTT_TOPIC_MY_IP, WiFi.localIP().toString().c_str(), true);
}

inline void SendBreak()
{
    Serial2.updateBaudRate(9600);
    uint8_t buf[] = {0};
    Serial2.write(buf, sizeof(buf));
    Serial2.flush();
    Serial2.updateBaudRate(38400);
}

void loop() {
    // break
    SendBreak();

    //Serial2.write(data, 32);
    Serial2.write(data, CHANNEL_COUNT);
    Serial2.flush();

    loopUpdateServer();

    if (false == mqttConnected()) {
        mqttReconnect();
    }

    mqttLoop();
}

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
        // Add missing terminating null byte to payload
        payload[length] = '\0';

        int valueInt = atoi((const char *) payload);
        uint8_t value = valueInt & 0xFF;
        data[channel-1] = value;

        MZTX_DEBUG_PRINTLN("Channel line");
        MZTX_DEBUG_PRINTLN(channel);
        MZTX_DEBUG_PRINTLN(value);
    }
}
