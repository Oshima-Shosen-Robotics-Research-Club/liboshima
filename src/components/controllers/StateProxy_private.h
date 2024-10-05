#pragma once

#include <stdint.h>

/**
 * @brief ボタンの状態を管理するプロキシクラス
 */
template <typename StateType, typename EnumType, uint8_t BitWidth>
class StateProxy_private {
public:
  StateProxy_private(StateType &stateRef, uint8_t index)
      : stateRef(stateRef), index(index) {}

  StateProxy_private &operator=(EnumType value) {
    stateRef &= ~(static_cast<StateType>((1 << BitWidth) - 1) << (index * BitWidth)); // 対象ビットをクリア
    stateRef |= static_cast<StateType>(value) << (index * BitWidth); // 新しい状態をセット
    return *this;
  }

  operator EnumType() const {
    return static_cast<EnumType>((stateRef >> (index * BitWidth)) & ((1 << BitWidth) - 1)); // 対象ビットから状態を取得
  }

private:
  StateType &stateRef;
  uint8_t index;
};