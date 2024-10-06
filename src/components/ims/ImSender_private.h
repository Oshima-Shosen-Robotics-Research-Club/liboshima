#pragma once

#include <utils/Converter.h>
#include <utils/Debuglogger.h>

#define IM_SEND_INTERVAL 55

template <typename SerialType, typename LoggerType = DebugLogger<SerialType> *>
class ImSender_private {
public:
  ImSender_private(SerialType &serial, LoggerType logger = nullptr)
      : serial(serial), logger(logger) {}

  template <typename T> void send(const T &data) {
    static_assert(sizeof(T) >= 1 && sizeof(T) <= 32,
                  "Data size must be between 1 and 32 bytes");
    if (logger)
      logger->println("ImSender_private", "send", "Sending data");

    serial.print("TXDA ");
    for (uint8_t i = 0; i < sizeof(T); i++) {
      char hex[2];
      Converter::toHex(reinterpret_cast<const uint8_t *>(&data) + i, 1, hex);
      serial.print(hex);
    }
    serial.println();

    if (logger)
      logger->println("ImSender_private", "send", "Data sent");
  }

private:
  SerialType &serial;
  LoggerType logger;
};
