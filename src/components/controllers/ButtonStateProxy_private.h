// ButtonStateProxy_private.h
#pragma once

#include "ButtonStateEnum.h"
#include <stdint.h>

/**
 * @brief ボタンの状態を管理するプロキシクラス
 */
template <typename StateType> class ButtonStateProxy_private {
public:
  ButtonStateProxy_private(StateType &stateRef, uint8_t index)
      : stateRef(stateRef), index(index) {}

  ButtonStateProxy_private &operator=(ButtonStateEnum value) {
    stateRef &= ~(0b1 << index); // 対象ビットをクリア
    stateRef |= static_cast<uint8_t>(value) << index; // 新しい状態をセット
    return *this;
  }

  operator ButtonStateEnum() const {
    return static_cast<ButtonStateEnum>((stateRef >> index) &
                                        0b1); // 対象ビットから状態を取得
  }

private:
  StateType &stateRef;
  uint8_t index;
};