/**
 * @file BitWidthArray.h
 * @brief 任意のビット幅を持つ列挙型要素の配列を管理するクラス
 *
 * このヘッダーファイルは、要素ごとのビット幅を指定できる配列クラス
 * `BitWidthArray` を提供します。
 * 配列の要素は、指定されたビット幅に基づいて効率的に格納され、アクセスされます。
 * @note 配列のサイズや要素数はテンプレート引数として提供されます。
 */

#pragma once

#include "BitWidthElement.h"
#include <stdint.h>
#include <types/TypeSelector.h>

/**
 * @brief 要素のビット幅を指定できる配列クラス
 *
 * テンプレートで指定されたビット幅を持つ列挙型の要素を、効率的に管理します。
 * 配列自体は一つの整数型 (`TypeSelector` で決定される型)
 * によって表現され、各要素はその中の 特定のビット位置に格納されます。
 *
 * @tparam EnumType 列挙型のタイプ。格納される値の種類を指定します。
 * @tparam BitWidth
 * 各要素のビット幅を指定します。例えば、8ビットなら1要素は1バイト。
 * @tparam numElements 配列の要素数を指定します。
 */
template <typename EnumType, uint8_t elemBitSize, uint8_t numElements>
class BitWidthArray {
public:
  /// 配列を格納するための整数型を決定
  using Type = typename TypeSelector<numElements * elemBitSize>::Type;
  /// 各要素を管理するための型
  using ElementType = BitWidthElement<Type, EnumType, elemBitSize>;

  /**
   * @brief 配列の特定のインデックスにアクセスするための演算子
   *
   * 指定されたインデックスの位置にある要素を返します。
   *
   * @param index アクセスする要素のインデックス（0から `numElements-1` まで）。
   * @return ElementType 指定されたビット幅を持つ要素のラッパーオブジェクト
   */
  ElementType operator[](uint8_t index) {
    static_assert(
        sizeof(Type) < elemBitSize * numElements,
        "この配列は要素を格納するために十分なビット幅を持っていません");
    return ElementType(array, index);
  }

private:
  /// 配列データを格納する変数。すべての要素が一つの整数として格納されます。
  Type array = 0;
};
