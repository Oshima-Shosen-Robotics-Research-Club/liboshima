#pragma once

#include "ButtonStateArray_private.h"
#include "MotorStateArray_private.h"
#include <stdint.h>
#include <utils/Conditional.h>

/**
 * @file Controller.h
 * @brief コントローラの構造体定義
 *
 * このファイルには、コントローラの構造体定義が含まれています。
 * コントローラは、モーター用のボタン、その他のボタン、スティックの状態を管理します。
 * IM920SL構造体で送受信することができます。
 */

// アライメントを1バイトに設定
#pragma pack(push, 1)

typedef uint8_t ZeroSizeType[0];

/**
 * @brief コントローラ構造体
 *
 * @tparam numMotors モーターの数（デフォルトは0）
 * @tparam numButtons ボタンの数（デフォルトは0）
 * @tparam numSticks スティックの数（デフォルトは0）
 *
 * この構造体は、モーター、ボタン、スティックの状態を管理します。
 */
template <uint8_t numMotors = 0, uint8_t numButtons = 0, uint8_t numSticks = 0>
struct Controller {
public:
  /**
   * @brief MotorState型の配列
   *
   * モーターの状態を管理します。
   */
  typename conditional<numMotors != 0, MotorStateArray_private<numMotors>,
                       ZeroSizeType>::Type motors; ///< モーターの状態の配列

  /**
   * @brief ボタンの状態を格納する変数
   *
   * その他のボタンの状態を管理します。
   */
  typename conditional<numButtons != 0, ButtonStateArray_private<numButtons>,
                       ZeroSizeType>::Type buttons; ///< ボタンの状態の配列

  /**
   * @brief スティック構造体
   *
   * スティックのX軸とY軸の状態を管理します。
   */
  struct Stick {
    uint8_t x = 0;     ///< X軸の状態（0~255）
    uint8_t y = 0;     ///< Y軸の状態（0~255）
  } sticks[numSticks]; ///< スティックの状態の配列
};

#pragma pack(pop)
