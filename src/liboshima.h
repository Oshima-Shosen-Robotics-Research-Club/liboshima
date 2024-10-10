#pragma once

/**
 * @file liboshima.h
 * @brief Arduino IDE用のヘッダーファイル
 *
 * Arduino IDEではサブディレクトリが認識されないから。
 * 例：#include <parts\ims\IM920SL.h>はArduino IDEではできない。
 */

#include "parts/IM920SL.h"
#include "parts/LedTape.h"
#include "parts/cons/ControllerData.h"
#include "parts/motors/NonSpeedAdjustable.h"
#include "parts/motors/speed/BD62193.h"
#include "parts/motors/speed/TB67H450.h"
#include "utils/Converter.h"
#include "utils/DebugLogger.h"