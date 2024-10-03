#include <serials/SerialPort.h>
#include <utils/DebugLogger.h>

SerialPort serial(Serial);

void setup() { Logger.init(serial); }

void loop() {
  Logger.println("main", "loop", "Hello, world!");
  delay(1000);
}