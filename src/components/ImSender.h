#ifndef IM_SENDER_H
#define IM_SENDER_H

#include <SoftwareSerial.h>
#include "utils/DebugLogger.h"

class ImSender {
public:
  ImSender(uint8_t rxPin, uint8_t txPin, long baudRate);
  template <typename T> void send(const T &data) {
    serial.print("TXDA ");
    uint8_t buffer[sizeof(T)];
    serialize(data, buffer);
    serial.write(buffer, sizeof(T));
    serial.println();
  }

private:
  SoftwareSerial serial;
  template <typename T> void serialize(const T &data, uint8_t *buffer) {
    const uint8_t *dataPtr = (const uint8_t *)&data;
    for (size_t i = 0; i < sizeof(T); i++) {
      buffer[i] = dataPtr[i];
    }
    DebugLogger::printf("ImSender", "serialize", "Serialized data: %d\n", data);
  }
};

#endif // IM_SENDER_H
