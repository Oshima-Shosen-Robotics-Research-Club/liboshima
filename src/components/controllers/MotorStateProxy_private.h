// MotorStateProxy_private.h
// モーターの状態を管理するプロキシクラス
#pragma once

#include "MotorStateEnum.h"
#include <stdint.h>

/**
 * @brief モーターの状態を管理するプロキシクラス
 */
template <typename StateType> class MotorStateProxy_private {
public:
  MotorStateProxy_private(StateType &stateRef, uint8_t index)
      : stateRef(stateRef), index(index) {}

  MotorStateProxy_private &operator=(MotorStateEnum value) {
    stateRef &= ~(0b11 << (index * 2)); // 対象ビットをクリア
    stateRef |= static_cast<uint8_t>(value)
                << (index * 2); // 新しい状態をセット
    return *this;
  }

  operator MotorStateEnum() const {
    return static_cast<MotorStateEnum>((stateRef >> (index * 2)) &
                                       0b11); // 対象ビットから状態を取得
  }

private:
  StateType &stateRef;
  uint8_t index;
};