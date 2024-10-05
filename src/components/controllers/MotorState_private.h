#pragma once

#include "StateProxy_private.h"
#include "utils/types/TypeSelector.h"
#include <stdint.h>

/**
 * @brief モーターの状態を表す列挙型
 */
enum class MotorStateEnum : uint8_t {
  Stop = 0b00,    ///< 停止
  Forward = 0b01, ///< 前進
  Reverse = 0b10, ///< 後退
};

template <typename StateType>
using MotorStateProxy_private =
    StateProxy_private<StateType, MotorStateEnum, 2>;

/**
 * @brief モーターの状態を管理する配列クラス
 */
template <uint8_t numMotors> class MotorStateArray_private {
public:
  using Type = typename TypeSelector<numMotors * 2>::Type;

  MotorStateProxy_private<Type> operator[](uint8_t index) {
    return MotorStateProxy_private<Type>(state, index);
  }

private:
  Type state = 0;
};