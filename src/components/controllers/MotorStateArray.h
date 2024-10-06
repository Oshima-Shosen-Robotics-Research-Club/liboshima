/**
 * @file MotorStateArray.h
 * @brief モーターの状態を管理するためのクラスと列挙型を定義します。
 *
 * このファイルには、モーターの状態を表す列挙型と、複数のモーターの状態を効率的に管理するための
 * 配列クラスが含まれています。モーターの状態は、停止、前進、後退の3つの状態を持ちます。
 */

#pragma once

#include <nets/BitWidthArray.h>
#include <stdint.h>

/**
 * @brief モーターの状態を表す列挙型
 *
 * この列挙型は、モーターが停止、前進、後退のいずれかの状態にあることを表します。
 * 各状態は2ビットで表現され、以下の3つの状態があります。
 */
enum class MotorStateEnum : uint8_t {
  Stop = 0b00,    ///< モーターが停止している状態
  Forward = 0b01, ///< モーターが前進している状態
  Reverse = 0b10, ///< モーターが後退している状態
};

/**
 * @brief モーターの状態を管理する配列クラス
 *
 * このクラスは、複数のモーターの状態を効率的に管理するための配列を提供します。
 * 各モーターの状態は2ビットで表現され、`BitWidthArray`クラスを使用して管理されます。
 *
 * 使用例:
 * @code
 * // 4つのモーターの状態を管理するための配列を作成
 * MotorStateArray<4> motorStates;
 * // モーター1を前進させる
 * motorStates[0] = MotorStateEnum::Forward;
 * @endcode
 *
 * @tparam numMotors 管理するモーターの数（1以上の値でなければならない）
 */
template <uint8_t numMotors>
using MotorStateArray = BitWidthArray<MotorStateEnum, 2, numMotors>;
