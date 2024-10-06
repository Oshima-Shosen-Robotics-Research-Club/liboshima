#pragma once

#include "ImReceiver_private.h"
#include "ImSender_private.h"

template <typename SerialType, typename LoggerType = DebugLogger<SerialType> *>
class IM920SL : public ImReceiver_private<SerialType, LoggerType>,
                public ImSender_private<SerialType, LoggerType> {
public:
  IM920SL(SerialType &serial, LoggerType logger = nullptr)
      : ImReceiver_private<SerialType, LoggerType>(serial, logger),
        ImSender_private<SerialType, LoggerType>(serial, logger),
        serial(serial) {}

  void begin(unsigned long baudrate = 19200) { serial.begin(baudrate); }
  uint8_t available() { return serial.available(); }

private:
  SerialType &serial;
};
