#pragma once

/**
 * @file liboshima.h
 * @brief Arduino IDE用のヘッダーファイル
 *
 * Arduino IDEではサブディレクトリが認識されないから。
 * 例：#include <components\ims\IM920SL.h>はArduino IDEではできない。
 */

#include "components/LedTape.h"
#include "components/controllers/Controller.h"
#include "components/ims/IM920SL.h"
#include "components/ims/ImReceiver_private.h"
#include "components/ims/ImSender_private.h"
#include "components/motors/NonSpeedAdjustable.h"
#include "components/motors/speed/BD62193.h"
#include "components/motors/speed/ISpeedAdjustable.h"
#include "components/motors/speed/TB67H450.h"
#include "serials/SerialPort.h"
#include "utils/Converter.h"
#include "utils/DebugLogger.h"