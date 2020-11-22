#include <mqtt.h>

PubSubClient mqttClient(espClient);

void mqttInit(void)
{
    IPAddress ipAddr;
    ipAddr.fromString(MZTX_MQTT_IP);
    mqttClient.setServer(ipAddr, MZTX_MQTT_PORT);
    mqttClient.setCallback(mqttCallback);
}

bool mqttConnected(void)
{
    return mqttClient.connected();
}

void mqttReconnect(void)
{
    // Loop until we're reconnected
    while (false == mqttClient.connected())
    {
        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);

        // Attempt to connect
        if (mqttClient.connect(clientId.c_str()))
        {
            // Once connected, publish an announcement...
            //mqttClient.publish("outTopic", "hello world"); // @TODO Remove debug

            // ... and resubscribe
            //mqttClient.subscribe("inTopic");
        }
        else
        {
            // Wait 1 second before retrying
            delay(1000);
        }
    }
}

void mqttPublish(const char* topic, const char* payload, boolean retain)
{
    mqttClient.publish(topic, payload, retain);
}

void mqttSubscribe(const char* topic)
{
    mqttClient.subscribe(topic);
}

void mqttLoop(void)
{
    mqttClient.loop();
}
