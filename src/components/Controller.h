#pragma once

#include <stdint.h>

/**
 * @file Controller.h
 * @brief コントローラの構造体定義
 *
 * このファイルには、コントローラの構造体定義が含まれています。
 * コントローラは、モーター、ボタン、スティックの状態を管理します。
 */

// アライメントを1バイトに設定
#pragma pack(push, 1)

/**
 * @brief コントローラ構造体
 *
 * @tparam numMotors モーターの数（デフォルトは4）
 * @tparam numButtons ボタンの数（デフォルトは0）
 * @tparam numSticks スティックの数（デフォルトは0）
 *
 * この構造体は、モーター、ボタン、スティックの状態を管理します。
 */
template <uint8_t numMotors = 4, uint8_t numButtons = 0, uint8_t numSticks = 0>
struct Controller {
  /**
   * @brief ボタンの状態を格納する変数
   *
   * ボタンの状態をビットフィールドとして格納します。
   */
  uint32_t buttons : numButtons;

  /**
   * @brief モーター構造体
   *
   * モーターのピン状態を管理します。
   */
  struct Motor {
    uint8_t pin1 : 1;  ///< ピン1の状態（1ビット）
    uint8_t pin2 : 1;  ///< ピン2の状態（1ビット）
  } motors[numMotors]; ///< モーターの配列

  /**
   * @brief スティック構造体
   *
   * スティックのX軸とY軸の状態を管理します。
   */
  struct Stick {
    uint8_t x;         ///< X軸の状態
    uint8_t y;         ///< Y軸の状態
  } sticks[numSticks]; ///< スティックの配列
};

#pragma pack(pop)