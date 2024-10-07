/**
 * @file ControllerData.h
 * @brief コントローラの構造体定義
 *
 * このファイルには、コントローラの構造体定義が含まれています。
 * コントローラは、モーター用のボタン、その他のボタン、スティックの状態を管理します。
 * IM920SL構造体で送受信することができます。
 */

#pragma once

#include "ButtonStateArray.h"
#include "MotorStateArray.h"
#include <stdint.h>
#include <types/Conditional.h>
#include <types/ZeroType.h>

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
   * @brief MotorState型の配列
   *
   * モーターの状態を管理します。
   * `numMotors` が0の場合、サイズ0の配列（`ZeroSizeType`）が使用されます。
   */
  typename Conditional<numMotors == 0, ZeroSizeType,
                       MotorStateArray<numMotors>>::Type
      motors; ///< モーターの状態の配列

  /**
   * @brief ボタンの状態を格納する変数
   *
   * その他のボタンの状態を管理します。
   * `numButtons` が0の場合、サイズ0の配列（`ZeroSizeType`）が使用されます。
   */
  typename Conditional<numButtons == 0, ZeroSizeType,
                       ButtonStateArray<numButtons>>::Type
      buttons; ///< ボタンの状態の配列

  /**
   * @brief スティック構造体
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
