// TypeSelector.h
#pragma once

#include "Conditional.h"
#include <stddef.h>
#include <stdint.h>

/**
 * @brief 型選択を行うテンプレートクラス
 */
template <size_t N> struct TypeSelector {
  using Type = typename Conditional<
      (N <= 8), uint8_t,
      typename Conditional<(N <= 16), uint16_t,
                           typename Conditional<(N <= 32), uint32_t,
                                                uint64_t>::Type>::Type>::Type;
};