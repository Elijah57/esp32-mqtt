#include <Arduino.h>
#include <WiFi.h>
#include "wifi_manager.h"
#include "secrets.h"

bool connectWifi(unsigned long timeoutMs) {
  WiFi.onEvent(onWifiEvent);
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - start > timeoutMs) {
      Serial.printf("\nFailed, status %d\n", WiFi.status());
      return false;
    }
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected");
  return true;
}

void printWifiInfo() {
  Serial.println("");
  Serial.printf("SSID:     %s\n", WiFi.SSID().c_str());
  Serial.printf("IP:       %s\n", WiFi.localIP().toString().c_str());
  Serial.printf("Gateway:  %s\n", WiFi.gatewayIP().toString().c_str());   // your router
  Serial.printf("Subnet:   %s\n", WiFi.subnetMask().toString().c_str());
  Serial.printf("DNS:      %s\n", WiFi.dnsIP().toString().c_str());
  Serial.printf("MAC:      %s\n", WiFi.macAddress().c_str());
  Serial.printf("Signal:   %d dBm\n", WiFi.RSSI());
  Serial.printf("Channel:  %d\n", WiFi.channel());
}

// Event handler for WiFi events
void onWifiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
  switch (event) {
    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
      Serial.println("[wifi] associated with router");
      break;
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.printf("[wifi] got IP %s\n", WiFi.localIP().toString().c_str());
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.printf("[wifi] lost connection, reason %d\n",
                    info.wifi_sta_disconnected.reason);
      break;
    default:
      break;
  }
}
