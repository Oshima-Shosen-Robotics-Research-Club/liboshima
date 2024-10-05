#pragma once

#include "MotorStateEnum.h"
#include "MotorStateProxy_private.h"
#include <stdint.h>
#include <utils/Conditional.h>

// ビット数に基づいて適切な型を選択するためのテンプレート
template <uint8_t numMotors> struct SelectStateType {
  // numMotors *
  // 2が32以下ならuint32_t、それ以上ならuint64_t、それ未満ならより小さい型に対応
  using Type = typename conditional<
      (numMotors * 2 <= 8), uint8_t,
      typename conditional<(numMotors * 2 <= 16), uint16_t,
                           typename conditional<(numMotors * 2 <= 32), uint32_t,
                                                uint64_t>::Type>::Type>::Type;
};

template <uint8_t numMotors> class MotorStateArray_private {
public:
  /**
   * @brief モーターの状態に対する配列風アクセス
   * @param index モーターのインデックス
   * @return MotorStateProxy_private モーターの状態プロキシ
   */
  MotorStateProxy_private<typename SelectStateType<numMotors>::Type>
  operator[](uint8_t index) {
    return MotorStateProxy_private<typename SelectStateType<numMotors>::Type>(
        state, index);
  }

  /**
   * @brief モーターの状態に対する配列風アクセス（const版）
   * @param index モーターのインデックス
   * @return MotorStateEnum モーターの状態
   */
  MotorStateEnum operator[](uint8_t index) const {
    return static_cast<MotorStateEnum>((state >> (index * 2)) & 0b11);
  }

private:
  // numMotorsに応じた型を選択する
  typename SelectStateType<numMotors>::Type state;
};
