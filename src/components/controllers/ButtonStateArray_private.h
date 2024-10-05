// ButtonStateArray_private.h
#pragma once

#include "ButtonStateEnum.h"
#include "ButtonStateProxy_private.h"
#include <stdint.h>
#include <utils/Conditional.h>

template <uint8_t numButtons> class ButtonStateArray_private {
public:
  // ビット数に基づいて適切な型を選択するためのテンプレート
  struct SelectStateType {
    // numButtonsが8以下ならuint8_t、それ以上ならuint16_t、それ未満ならより小さい型に対応
    using Type = typename conditional<
        (numButtons <= 8), uint8_t,
        typename conditional<(numButtons <= 16), uint16_t,
                             typename conditional<(numButtons <= 32), uint32_t,
                                                  uint64_t>::Type>::Type>::Type;
  };
  /**
   * @brief ボタンの状態に対する配列風アクセス
   * @param index ボタンのインデックス
   * @return ButtonStateProxy_private ボタンの状態プロキシ
   */
  ButtonStateProxy_private<typename SelectStateType::Type>
  operator[](uint8_t index) {
    return ButtonStateProxy_private<typename SelectStateType::Type>(state,
                                                                    index);
  }

  /**
   * @brief ボタンの状態に対する配列風アクセス（const版）
   * @param index ボタンのインデックス
   * @return ButtonStateEnum ボタンの状態
   */
  ButtonStateEnum operator[](uint8_t index) const {
    return static_cast<ButtonStateEnum>((state >> index) & 0b1);
  }

private:
  // numButtonsに応じた型を選択する
  typename SelectStateType::Type state = 0;
};