#include <liboshima.h>

DebugLogger<HardwareSerial> logger(Serial);

void setup() { logger.init(serial); }

void loop() {
  logger.println("main", "loop", "Hello, world!");
  delay(1000);
}