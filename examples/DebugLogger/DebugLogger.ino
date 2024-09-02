#include <utils/DebugLogger.h>

void setup() {
  DebugLogger::init(Serial);
}

void loop() {
  DebugLogger::println("main", "loop", "Hello, world!\n");
  delay(1000);
}