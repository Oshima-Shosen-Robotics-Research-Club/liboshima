#include "IM920SL.h"

IM920SL::IM920SL(SerialPort &serial)
    : ImReceiver_private(serial), ImSender_private(serial), serial(serial) {}

void IM920SL::begin(unsigned long baudrate) { serial.begin(baudrate); }
