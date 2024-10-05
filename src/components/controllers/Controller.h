#pragma once

#include "MotorStateArray_private.h"
#include <stdint.h>

/**
 * @file Controller.h
 * @brief コントローラのクラス定義
 *
 * このファイルには、コントローラのクラス定義が含まれています。
 * コントローラは、モーター用のボタン、その他のボタン、スティックの状態を管理します。
 * IM920SLクラスで送受信することができます。
 */

// アライメントを1バイトに設定
#pragma pack(push, 1)

/**
 * @brief コントローラクラス
 *
 * @tparam numMotors モーターの数（デフォルトは0）
 * @tparam numButtons ボタンの数（デフォルトは0）
 * @tparam numSticks スティックの数（デフォルトは0）
 *
 * このクラスは、モーター、ボタン、スティックの状態を管理します。
 */
template <uint8_t numMotors = 0, uint8_t numButtons = 0, uint8_t numSticks = 0>
class Controller {
public:
  /**
   * @brief MotorState型の配列
   *
   * モーターの状態を管理します。
   */
  MotorStateArray_private<numMotors> motors; ///< モーターの状態の配列

  /**
   * @brief ボタンの状態を格納する変数
   *
   * その他のボタンの状態を管理します。
   */
  uint32_t buttons : numButtons + 1;

  /**
   * @brief スティック構造体
   *
   * スティックのX軸とY軸の状態を管理します。
   */
  struct Stick {
    uint8_t x;             ///< X軸の状態（0~255）
    uint8_t y;             ///< Y軸の状態（0~255）
  } sticks[numSticks + 1]; ///< スティックの配列
};

#pragma pack(pop)