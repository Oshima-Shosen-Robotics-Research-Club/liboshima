#include "Fastino.h"
#include <HardwareSerial.h>

int main() {
  setup();
  while (true) {
    loop();
  }
  return 0;
}

SerialPort FSerialPort(FastSerial);
SerialPort HSerialPort(Serial);