#include <Arduino.h>
// #include <WiFi.h>
#include "WiFiClient.h"
#include "wifi_manager.h"
#include "http_test.h"
#include <PubSubClient.h>
#include "secrets.h"

WiFiClient newWifiClient;
PubSubClient mqtt(newWifiClient);

void setup() {
  Serial.begin(115200);

  if (connectWifi()) {
    printWifiInfo();
  }


  mqtt.setServer(MQTT_HOST, MQTT_PORT);
  Serial.print("MQTT connecting... ");
    if (mqtt.connect("esp32-node-01")) {    // the actual connection happens here
      Serial.println("connected");
      mqtt.publish("home/esp32/hello", "hello from esp32");
    } else {
      Serial.printf("failed, state=%d\n", mqtt.state());
    }
}

void loop() {

    mqtt.loop();

    printWifiInfo();
    delay(3000);

    fetchTest();

}
