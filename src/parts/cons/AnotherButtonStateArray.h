/**
 * @file AnotherButtonStateArray.h
 * @brief ボタンの状態を管理するためのクラスと列挙型を定義します。
 *
 * このファイルには、ボタンの状態を表す列挙型と、複数のボタンの状態を効率的に管理するための
 * 配列クラスが含まれています。各ボタンの状態は1ビットで表現され、`BitWidthArray`
 * クラスを使用して管理されます。
 */

#pragma once

#include <stdint.h>
#include <types/nets/BitWidthArray.h>

/**
 * @brief ボタンの状態を表す列挙型
 *
 * この列挙型は、ボタンが押されているか離されているかを表します。
 * 各状態は1ビットで表現され、`RELEASED` および `PRESSED`
 * の2つの状態を持ちます。
 */
enum class AnotherButtonStateEnum : uint8_t {
  RELEASED = 0b0, ///< ボタンが離されている状態
  PRESSED = 0b1   ///< ボタンが押されている状態
};

/**
 * @brief ボタンの状態を管理する配列クラス
 *
 * このクラスは、複数のボタンの状態を効率的に管理するための配列を提供します。
 * 各ボタンの状態は1ビットで表現され、`BitWidthArray`
 * クラスを使用して管理されます。
 *
 * 使用例:
 * @code
 * // 5つのボタンの状態を管理するための配列を作成
 * AnotherButtonStateArray<5> buttonStates;
 * // ボタン1の状態を設定
 * buttonStates[0] = AnotherButtonStateEnum::PRESSED;
 * @endcode
 *
 * @tparam numButtons 管理するボタンの数（1以上の値でなければならない）
 */
template <uint8_t numButtons>
using AnotherButtonStateArray =
    BitWidthArray<AnotherButtonStateEnum, 1, numButtons>;