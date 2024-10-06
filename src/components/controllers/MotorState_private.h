#pragma once

#include <stdint.h>
#include <utils/nets/BitWidthArray.h>

/**
 * @brief モーターの状態を表す列挙型
 */
enum class MotorStateEnum : uint8_t {
  Stop = 0b00,    ///< 停止
  Forward = 0b01, ///< 前進
  Reverse = 0b10, ///< 後退
};

/**
 * @brief モーターの状態を管理する配列クラス
 */
template <uint8_t numMotors>
using MotorStateArray_private = BitWidthArray<MotorStateEnum, 2, numMotors>;