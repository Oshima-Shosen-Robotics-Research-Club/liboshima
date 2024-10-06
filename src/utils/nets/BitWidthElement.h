// BitWidthElement.h
#pragma once

#include <stdint.h>

/**
 * @brief 要素のビットサイズを指定可能な配列の要素を管理するクラス
 */
template <typename ArrayType, typename EnumType, uint8_t BitWidth>
class BitWidthElement {
public:
  BitWidthElement(ArrayType &arrayRef, uint8_t index)
      : arrayRef(arrayRef), index(index) {}

  BitWidthElement &operator=(EnumType value) {
    arrayRef &= ~(static_cast<ArrayType>((1 << BitWidth) - 1)
                  << (index * BitWidth)); // 対象ビットをクリア
    arrayRef |= static_cast<ArrayType>(value)
                << (index * BitWidth); // 新しい状態をセット
    return *this;
  }

  operator EnumType() const {
    return static_cast<EnumType>(
        (arrayRef >> (index * BitWidth)) &
        ((1 << BitWidth) - 1)); // 対象ビットから状態を取得
  }

private:
  ArrayType &arrayRef;
  uint8_t index;
};