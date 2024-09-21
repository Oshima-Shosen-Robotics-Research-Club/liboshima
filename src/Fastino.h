#pragma once

#include <components/LedTape.h>
#include <components/ims/ImReceiver.h>
#include <components/ims/ImSender.h>
#include <components/motors/BD62193.h>
#include <components/motors/MotorDriver.h>
#include <components/motors/TB67H450.h>
#include <components/servos/HS_485HB.h>
#include <components/servos/MG90S.h>
#include <digitalWriteFast.h>
#include <serials/FastSerial.h>
#include <serials/SerialPort.h>
#include <utils/Converter.h>
#include <utils/DebugLogger.h>

void setup();
void loop();
extern SerialPort FSerialPort;
extern SerialPort HSerialPort;