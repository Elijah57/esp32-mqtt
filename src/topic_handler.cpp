#include <string.h>
#include "topics.h"   // include your own header first, so extern is seen before the definitions

const TopicEntry SUBSCRIBED_TOPICS[] = {
  { "home/esp32/led",    Topic::Led    },
  { "home/esp32/temp",   Topic::Temp   },
  { "home/esp32/status", Topic::Status },
};

const size_t SUBSCRIBED_TOPICS_COUNT =
    sizeof(SUBSCRIBED_TOPICS) / sizeof(SUBSCRIBED_TOPICS[0]);

Topic getTopicFromString(const char* s) {
  for (size_t i = 0; i < SUBSCRIBED_TOPICS_COUNT; i++) {
    if (strcmp(s, SUBSCRIBED_TOPICS[i].name) == 0) {
      return SUBSCRIBED_TOPICS[i].topicId;
    }
  }
  return Topic::Unknown;
}


const Topic getTopicFromString (const char* s) {
    for (const TopicEntry& entry : SUBSCRIBED_TOPICS) {
        if (strcmp(s, entry.name) == 0) {
            return entry.topicId;
        }
    }
    return Topic::Unknown;
}

// One small handler per topic
static void handleLed(const char* msg) {
  digitalWrite(LED_PIN, strcmp(msg, "ON") == 0 ? HIGH : LOW);
}

static void handleTemp(const char* msg) {

}

static void handleStatus(const char* msg) {

}
