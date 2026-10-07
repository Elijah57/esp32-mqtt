#include<Arduino.h>
#include<WiFiClient.h>
#include<PubSubClient.h>
#include"secrets.h"
#include "topic_handler.h"


static const char* CLIENT_ID    = "esp32-node-01";

// topic to publish to
static const char* TOPIC_TEMP   = "home/esp32/temperature";
static const char* TOPIC_LED    = "home/esp32/led";
static const char* TOPIC_STATUS = "home/esp32/status";
static const int   LED_PIN      = 2;

static WiFiClient netClient;
static PubSubClient mqtt(netClient);

static unsigned long lastReconnectAttempt = 0;


static void onMessage(char* topic, byte* payload, unsigned int length) {
  char msg[32];
  unsigned int n = (length < sizeof(msg) - 1) ? length : sizeof(msg) - 1;
  memcpy(msg, payload, n);
  msg[n] = '\0';
  Serial.printf("got '%s' on %s\n", msg, topic);

  if (strcmp(topic, TOPIC_LED) == 0) {
    digitalWrite(LED_PIN, strcmp(msg, "ON") == 0 ? HIGH : LOW);
  }
}


void mqttSetup() {
    mqtt.setServer(MQTT_HOST, MQTT_PORT);
}

void mqttLoop() {

}

void mqttPublishTemp(float temp) {

}

bool mqttIsConnected() {

}




// Router for mqtt events
void topicRouter(char* str, const char* msg) {
  switch (getTopicFromString(str)) {
    case Topic::Temp:
      Serial.println("[wifi] associated with router");
      break;
    case Topic::Led:
      handleLed(msg);
      break;
    case Topic::Status:
      Serial.printf("[wifi] lost connection, reason %d\n",
                    );
      break;
    default:
      break;
  }
}


// handler for mqtt events

// One small handler per topic
static void handleLed(const char* msg) {
  digitalWrite(LED_PIN, strcmp(msg, "ON") == 0 ? HIGH : LOW);
}

static void handleTemp(const char* msg) {

}

static void handleStatus(const char* msg) {

}
