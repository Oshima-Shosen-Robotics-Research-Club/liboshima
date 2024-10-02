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
 * @tparam numMotors モーターの数（デフォルトは0）
 * @tparam numButtons ボタンの数（デフォルトは0）
 * @tparam numSticks スティックの数（デフォルトは0）
 *
 * この構造体は、モーター、ボタン、スティックの状態を管理します。
 */
template <uint8_t numMotors = 0, uint8_t numButtons = 0, uint8_t numSticks = 0>
struct Controller {

  /**
   * @brief モーター構造体
   *
   * モーターのピン状態を管理します。
   */
  struct Motor {
    uint8_t forward : 1;   ///< 前進ピンの状態（0または1）
    uint8_t reverse : 1;   ///< 後進ピンの状態（0または1）
  } motors[numMotors + 1]; ///< モーターの配列

  /**
   * @brief ボタンの状態を格納する変数
   *
   * ボタンの状態をビットフィールドとして格納します。
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