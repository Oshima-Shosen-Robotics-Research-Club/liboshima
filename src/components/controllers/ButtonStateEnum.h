// ButtonStateEnum.h
#pragma once

#include <stdint.h>

/**
 * @brief ボタンの状態を表す列挙型
 */
enum class ButtonStateEnum : uint8_t {
  Released = 0b0, ///< 離されている
  Pressed = 0b1   ///< 押されている
};