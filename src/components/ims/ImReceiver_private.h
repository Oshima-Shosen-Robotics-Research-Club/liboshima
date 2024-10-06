#pragma once

#include <utils/Converter.h>
#include <utils/Debuglogger.h>

#define IM_RECEIVE_INTERVAL_MILLIS 500
#define IM_RECEIVE_INTERVAL_MICROS 500000

template <typename SerialType, typename LoggerType = DebugLogger<SerialType> *>
class ImReceiver_private {
public:
  ImReceiver_private(SerialType &serial, LoggerType logger = nullptr)
      : serial(serial), logger(logger) {}

  enum class ErrorCode {
    SUCCESS,
    NO_DATA_AVAILABLE,
    RECEIVED_STRING_LENGTH_INVALID,
    COLON_NOT_FOUND,
    DATA_STRING_INVALID,
  };

  template <typename T> ErrorCode receive(T &data) {
    static_assert(sizeof(T) >= 1 && sizeof(T) <= 32,
                  "Data size must be between 1 and 32 bytes");

    if (logger)
      logger->println("ImReceiver_private", "receive", "Receiving data");

    if (!serial.available()) {
      if (logger)
        logger->println("ImReceiver_private", "receive", "No data available");
      return ErrorCode::NO_DATA_AVAILABLE;
    }

    char recvedStr[10 + 1 + 32 * 2 + 31 + 1];
    size_t length =
        serial.readBytesUntil('\r', recvedStr, sizeof(recvedStr) - 1);
    recvedStr[length] = '\0';
    while (!serial.available())
      ;
    serial.read();

    if (logger)
      logger->printlnf("ImReceiver_private", "receive", "Received: %s",
                       recvedStr);

    if (length != 10 + 1 + sizeof(T) * 2 + sizeof(T) - 1) {
      if (logger)
        logger->printlnf("ImReceiver_private", "receive",
                         "Received string length invalid: %d", length);
      return ErrorCode::RECEIVED_STRING_LENGTH_INVALID;
    }

    if (recvedStr[10] != ':') {
      if (logger)
        logger->println("ImReceiver_private", "receive", "Colon not found");
      return ErrorCode::COLON_NOT_FOUND;
    }

    char *pos = recvedStr + 11;
    for (size_t i = 0; i < sizeof(T); i++) {
      Converter::fromHex(pos, 2, reinterpret_cast<uint8_t *>(&data) + i);
      pos += 2;
      if (*pos == ',') {
        pos++;
      }
    }

    if (logger)
      logger->println("ImReceiver_private", "receive", "Data received");
    return ErrorCode::SUCCESS;
  }

private:
  SerialType &serial;
  LoggerType logger;
};
