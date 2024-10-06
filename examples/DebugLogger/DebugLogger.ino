// Arduino IDEの場合は "#include <liboshima.h>" としてください。
#include <utils/DebugLogger.h>

DebugLogger<HardwareSerial> logger(Serial);

void setup() { logger.init(serial); }

void loop() {
  logger.println("main", "loop", "Hello, world!");
  delay(1000);
}