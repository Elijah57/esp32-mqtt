#pragma once
#include <stddef.h>

enum class Topic {
  Unknown,
  Temp,
  Led,
  Status,
};

struct TopicEntry {
  const char* name;
  Topic       topicId;
};

extern const TopicEntry SUBSCRIBED_TOPICS[];     // declared here, defined in the .cpp
extern const size_t     SUBSCRIBED_TOPICS_COUNT;

Topic getTopicFromString(const char* s);
