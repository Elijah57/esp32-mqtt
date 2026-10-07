#pragma once



void mqttSetup();                 // call once in setup(), after Wi-Fi is connected
void mqttLoop();                  // call every loop() iteration
void mqttPublishTemp(float temp); // publish a reading (does nothing if not connected)
bool mqttIsConnected();
