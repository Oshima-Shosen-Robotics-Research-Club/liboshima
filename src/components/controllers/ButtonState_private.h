#pragma once

#include "StateProxy_private.h"
#include "utils/types/TypeSelector.h"
#include <stdint.h>

/**
 * @brief ボタンの状態を表す列挙型
 */
enum class ButtonStateEnum : uint8_t {
  Released = 0b0, ///< 離されている
  Pressed = 0b1   ///< 押されている
};

template <typename StateType>
using ButtonStateProxy_private =
    StateProxy_private<StateType, ButtonStateEnum, 1>;

/**
 * @brief ボタンの状態を管理する配列クラス
 */
template <uint8_t numButtons> class ButtonStateArray_private {
public:
  using Type = typename TypeSelector<numButtons>::Type;

  ButtonStateProxy_private<Type> operator[](uint8_t index) {
    return ButtonStateProxy_private<Type>(state, index);
  }

private:
  Type state = 0;
};