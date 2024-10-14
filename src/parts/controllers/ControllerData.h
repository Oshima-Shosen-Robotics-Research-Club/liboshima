/**
 * @file ControllerData.h
 * @brief コントローラの構造体定義
 *
 * このファイルには、コントローラの構造体定義が含まれています。
 * コントローラは、モーター用のボタン、その他のボタン、スティックの状態を管理します。
 * IM920SLクラスで送受信することができます。
 */

#pragma once

#include "AnotherButtonStateArray.h"
#include "MotorButtonStateArray.h"
#include <stdint.h>
#include <types/Conditional.h>
#include <types/ZeroSizeType.h>

// アライメントを1バイトに設定
#pragma pack(push, 1)

/**
 * @brief コントローラ構造体
 *
 * この構造体は、モーター、ボタン、スティックの状態を管理します。
 * 各メンバーは、指定された数のモーター、ボタン、およびスティックの状態を保持します。
 *
 * @tparam numMotors モーターの数（デフォルトは0）
 * @tparam numButtons ボタンの数（デフォルトは0）
 * @tparam numSticks スティックの数（デフォルトは0）
 */
template <uint8_t numMotors = 0, uint8_t numButtons = 0, uint8_t numSticks = 0>
struct ControllerData {
public:
  /**
   * @brief モーター専用のボタンの状態を管理する配列
   *
   * `numMotors` が0の場合、サイズ0の配列（`ZeroSizeType`）が使用されます。
   * それ以外の場合、`MotorButtonStateArray<numMotors>` 型の配列が使用されます。
   */
  typename Conditional<numMotors == 0, ZeroSizeType,
                       MotorButtonStateArray<numMotors>>::Type
      motorButtons; ///< モーターの状態の配列

  /**
   * @brief ボタンの状態を管理する配列
   *
   * `numButtons` が0の場合、サイズ0の配列（`ZeroSizeType`）が使用されます。
   * それ以外の場合、`AnotherButtonStateArray<numButtons>`
   * 型の配列が使用されます。
   */
  typename Conditional<numButtons == 0, ZeroSizeType,
                       AnotherButtonStateArray<numButtons>>::Type
      otherButtons; ///< ボタンの状態の配列

  /**
   * @brief スティックの状態を管理する構造体
   *
   * スティックのX軸とY軸の状態を管理します。
   * 配列のサイズは、`numSticks` に基づいて決定されます。
   */
  struct Stick {
    uint8_t x = 0;     ///< X軸の状態（0~255）
    uint8_t y = 0;     ///< Y軸の状態（0~255）
  } sticks[numSticks]; ///< スティックの状態の配列
};

#pragma pack(pop)