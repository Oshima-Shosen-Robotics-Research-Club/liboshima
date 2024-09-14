#include <utils/DebugLogger.h>

void setup() { DebugLogger::init(0, 0); }

void loop() {
  DebugLogger::println("main", "loop", "Hello, world!");
  delay(1000);
}