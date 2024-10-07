#include <liboshima.h>

DebugLogger<HardwareSerial> logger(Serial);

void setup() { logger.begin(); }

void loop() {
  logger.println("main", "loop", "Hello, world!");
  delay(1000);
}