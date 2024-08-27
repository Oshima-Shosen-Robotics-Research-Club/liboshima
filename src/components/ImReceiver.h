#ifndef IM_RECEIVER_H
#define IM_RECEIVER_H

#include "utils/DebugLogger.h"
#include <SoftwareSerial.h>

class ImReceiver {
public:
  ImReceiver(uint8_t rxPin, uint8_t txPin, long baudRate);
  bool available();
  template <typename T> bool receive(T &data) {
    if (!available()) {
      DebugLogger::print("ImReceiver", "receive", "No data available\n");
      return false;
    }

    String recvedStr;
    char recvedChar;

    DebugLogger::print("ImReceiver", "receive", "Waiting for data...\n");

    // Wait for data to arrive and read it into the string
    while (true) {
      recvedChar = (char)serial.read();
      if (recvedChar == '\n') {
        break;
      } else {
        recvedStr += recvedChar;
      }
    }

    DebugLogger::printf("ImReceiver", "receive", "Received data: %s\n",
                        recvedStr.c_str());

    // Find the colon index using String::indexOf
    int colonIndex = recvedStr.indexOf(':');
    if (colonIndex == -1) {
      DebugLogger::print("ImReceiver", "receive", "Colon not found\n");
      return false;
    }

    // Extract the data after the colon
    String hexData = recvedStr.substring(colonIndex + 1);

    if (hexData.length() < sizeof(T) * 2) {
      DebugLogger::print("ImReceiver", "receive", "Data length is too short\n");
      return false;
    }

    uint8_t buffer[sizeof(T)];
    for (size_t i = 0; i < sizeof(T); i++) {
      String hexPair = hexData.substring(i * 2, i * 2 + 2);
      buffer[i] = (uint8_t)strtol(hexPair.c_str(), nullptr, 16);
    }

    // Deserialize buffer into data
    deserialize(buffer, data);
    return true;
  }

private:
  SoftwareSerial serial;
  template <typename T> void deserialize(uint8_t *buffer, T &data) {
    memcpy(&data, buffer, sizeof(T));
    DebugLogger::printf("ImReceiver", "deserialize", "Deserialized data: %d\n",
                        data);
  }
};

#endif // IM_RECEIVER_H