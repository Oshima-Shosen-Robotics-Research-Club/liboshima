/**
 * @file BitWidthElement.h
 * @brief ビット幅指定可能な配列の要素を管理するクラス
 *
 * このヘッダーファイルでは、 `BitWidthArray` クラスの要素を管理する
 * `BitWidthElement` クラスを定義します。
 * 特定のビット幅を持つ要素の読み書きを効率的に行うためのインターフェースを提供します。
 */

#pragma once

#include <stdint.h>

/**
 * @brief 特定のビット幅を持つ配列の要素を管理するクラス
 *
 * `BitWidthArray` の個々の要素をビット操作によって管理します。
 * このクラスは、配列内の特定のビット位置に対して、指定されたビット幅に基づいて値の設定や取得を行います。
 *
 * @tparam ArrayType 配列全体を格納する型（通常は整数型）。
 * @tparam EnumType 列挙型。要素に格納される値の型を指定します。
 * @tparam elemBitSize 各要素が占有するビット数。
 */
template <typename ArrayType, typename EnumType, uint8_t elemBitSize>
class BitWidthElement {
public:
  /**
   * @brief コンストラクタ
   *
   * 配列の特定のビット位置に対応する要素を初期化します。
   *
   * @param arrayRef 配列全体を参照するための参照型変数。
   * @param index
   * 要素の位置を指定するインデックス（ビット単位でのオフセット計算に使用）。
   */
  BitWidthElement(ArrayType &arrayRef, uint8_t index)
      : arrayRef(arrayRef), index(index) {}

  /**
   * @brief 要素に新しい値を代入するための代入演算子
   *
   * 指定されたビット幅の範囲内で、対象の配列要素の値を更新します。
   *
   * @param value 代入する列挙型の値。
   * @return BitWidthElement& 自分自身への参照を返します。
   */
  BitWidthElement &operator=(EnumType value) {
    // 対象ビット範囲をクリア
    arrayRef &= ~(static_cast<ArrayType>((1 << elemBitSize) - 1)
                  << (index * elemBitSize));
    // 新しい値をセット
    arrayRef |= static_cast<ArrayType>(value) << (index * elemBitSize);
    return *this;
  }

  /**
   * @brief 暗黙のキャスト演算子
   *
   * 要素の値を列挙型に変換して返します。ビットシフトとマスク操作により、配列から指定ビット幅の値を取得します。
   *
   * @return EnumType ビット幅に対応する列挙型の値を返します。
   */
  operator EnumType() const {
    return static_cast<EnumType>((arrayRef >> (index * elemBitSize)) &
                                 ((1 << elemBitSize) - 1));
  }

private:
  /// 配列全体への参照。ビット操作を通じて値を設定・取得する対象。
  ArrayType &arrayRef;
  /// 操作対象の要素のインデックス（ビット単位での位置）。
  uint8_t index;
};