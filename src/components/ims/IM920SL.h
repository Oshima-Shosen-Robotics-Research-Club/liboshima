#pragma once

#include "ImReceiver.h"
#include "ImSender.h"

template <typename SerialType, typename LoggerType = DebugLogger<SerialType> *>
class IM920SL : public ImReceiver<SerialType, LoggerType>,
                public ImSender<SerialType, LoggerType> {
public:
  IM920SL(SerialType &serial, LoggerType logger = nullptr)
      : ImReceiver<SerialType, LoggerType>(serial, logger),
        ImSender<SerialType, LoggerType>(serial, logger), serial(serial) {}

  void begin(unsigned long baudrate = 19200) { serial.begin(baudrate); }
  uint8_t available() { return serial.available(); }

private:
  SerialType &serial;
};
