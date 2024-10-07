/**
 * @file TypeSelector.h
 * @brief 数値に基づいて適切な整数型を選択するテンプレートクラス
 *
 * このヘッダーファイルは、指定されたビット数に基づいて適切な符号なし整数型を選択する
 * `TypeSelector` クラスを提供します。
 * 8ビット、16ビット、32ビット、64ビットの範囲で型を選択します。
 *
 * @note `Conditional` をネストして利用し、 `N`
 * の値に基づいて最適な型を決定します。
 */

#pragma once

#include "Conditional.h"
#include <stddef.h>
#include <stdint.h>

/**
 * @brief ビット数に応じて型を選択するクラス
 *
 * このクラスは、指定されたビット数 `N` に基づき、`uint8_t`, `uint16_t`,
 * `uint32_t`, `uint64_t` のいずれかの型を選択します。 例えば、`N <= 8` の場合は
 * `uint8_t` が選択されます。
 *
 * @tparam N 必要なビット数（8, 16, 32, 64ビットのいずれか）
 */
template <size_t N> struct TypeSelector {
  /// `N` に基づいて選択される符号なし整数型
  using Type = typename Conditional<
      (N <= 8), uint8_t, ///< 8ビット以下の場合 `uint8_t`
      typename Conditional<
          (N <= 16), uint16_t, ///< 16ビット以下の場合 `uint16_t`
          typename Conditional<(N <= 32), uint32_t, ///< 32ビット以下の場合
                                                    ///< `uint32_t`
                               uint64_t ///< それ以外の場合 `uint64_t`
                               >::Type>::Type>::Type;
};
