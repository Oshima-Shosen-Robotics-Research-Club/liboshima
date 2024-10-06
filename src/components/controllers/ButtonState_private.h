#pragma once

#include <stdint.h>
#include <utils/nets/BitWidthArray.h>

/**
 * @brief ボタンの状態を表す列挙型
 */
enum class ButtonStateEnum : uint8_t {
  Released = 0b0, ///< 離されている
  Pressed = 0b1   ///< 押されている
};

/**
 * @brief ボタンの状態を管理する配列クラス
 */
template <uint8_t numButtons>
using ButtonStateArray_private = BitWidthArray<ButtonStateEnum, 1, numButtons>;