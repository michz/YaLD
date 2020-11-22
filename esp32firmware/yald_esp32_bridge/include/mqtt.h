#ifndef __MQTT_H_
#define __MQTT_H_

#include <PubSubClient.h>

#include <main.h>
#include <credentials.h>

extern PubSubClient mqttClient;

 void mqttInit(void);
 bool mqttConnected(void);
 void mqttReconnect(void);
 void mqttPublish(const char* topic, const char* payload, boolean retain);
 void mqttLoop(void);
 void mqttSubscribe(const char* topic);

 void mqttCallback(char* topic, byte* payload, unsigned int length);

 #endif
