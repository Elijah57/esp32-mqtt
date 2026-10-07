#pragma once
#include <WiFi.h>

bool connectWifi(unsigned long timeoutMs = 15000);
void printWifiInfo();
void onWifiEvent(WiFiEvent_t event, WiFiEventInfo_t info);
