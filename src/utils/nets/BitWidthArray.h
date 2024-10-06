// BitWidthArray.h
#pragma once

#include "BitWidthElement.h"
#include "utils/types/TypeSelector.h"
#include <stdint.h>

/**
 * @brief 要素のビットサイズを指定可能な配列クラス
 */
template <typename EnumType, uint8_t BitWidth, uint8_t numElements>
class BitWidthArray {
public:
  using Type = typename TypeSelector<numElements * BitWidth>::Type;
  using ElementType = BitWidthElement<Type, EnumType, BitWidth>;

  ElementType operator[](uint8_t index) { return ElementType(array, index); }

private:
  Type array = 0;
};