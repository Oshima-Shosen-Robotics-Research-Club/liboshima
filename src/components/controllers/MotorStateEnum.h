#pragma once

#include <stdint.h>

/**
 * @brief モーターの状態を表す列挙型
 */
enum class MotorStateEnum : uint8_t {
  Stop = 0b00,    ///< 停止
  Forward = 0b01, ///< 前進
  Reverse = 0b10, ///< 後退
};