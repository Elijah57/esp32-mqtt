#include <HTTPClient.h>


void fetchTest() {
  HTTPClient http;
  http.begin("http://example.com");     // plain HTTP, no certificate setup needed
  int code = http.GET();                // blocks until the reply arrives
  Serial.printf("HTTP status: %d\n", code);
  if (code > 0) {
    Serial.println(http.getString().substring(0, 200));   // first 200 characters
  }
  http.end();
}
