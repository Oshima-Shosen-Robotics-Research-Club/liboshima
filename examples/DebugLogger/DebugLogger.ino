#include <liboshima.h>

DebugLogger<HardwareSerial> logger(Serial);

void setup() { logger.begin(); }

void loop() {
  logger.println(DebugLogger<HardwareSerial>::LogLevel::INFO,
                 DebugLogger<HardwareSerial>::WaitMode::NO_WAIT, "Main", "loop",
                 "Hello, world!");
  delay(1000);
}