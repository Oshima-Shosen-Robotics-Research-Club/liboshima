#include <liboshima.h>

DebugLogger<HardwareSerial> logger(Serial);

void setup() { logger.begin(); }

void loop() {
  logger.println(DebugLoggerLevel::INFO, DebugLoggerMode::NO_WAIT, "Main",
                 "loop", "Hello, world!");
  delay(1000);
}