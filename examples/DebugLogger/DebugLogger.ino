#include <utils/DebugLogger.h>

void setup() {
  Serial.begin(19200);
  DebugLogger::init(Serial);
}

void loop() {
  DebugLogger::println("main", "loop", "Hello, world!");
  delay(1000);
}