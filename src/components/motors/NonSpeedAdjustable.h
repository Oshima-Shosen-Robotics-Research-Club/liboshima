/**
 * @file NonSpeedAdjustable.h
 * @brief 非速度調整可能なモーター制御クラスのヘッダファイル
 *
 * このクラスは、指定した2つのピンを使用してモーターを制御します。
 * モーターは前進、後進、停止の3つの動作を行うことができます。
 *
 * @note Arduino環境で使用されることを前提としています。
 */

#pragma once

#include <Arduino.h>

/**
 * @class NonSpeedAdjustable
 * @brief 非速度調整可能なモーター制御クラス
 *
 * このクラスは、2つのデジタルピンを使用してモーターを前進、後進、停止させるためのメソッドを提供します。
 */
class NonSpeedAdjustable {
public:
  /**
   * @brief コンストラクタ
   *
   * 指定されたピン番号を使用してNonSpeedAdjustableクラスのインスタンスを初期化します。
   *
   * @param pin1 モーターの前進信号を制御するデジタルピン番号
   * @param pin2 モーターの後進信号を制御するデジタルピン番号
   */
  NonSpeedAdjustable(uint8_t pin1, uint8_t pin2);

  /**
   * @brief モーターを前進させる
   *
   * モーターを前進方向に回転させるためのメソッドです。
   */
  void forward();

  /**
   * @brief モーターを後進させる
   *
   * モーターを後進方向に回転させるためのメソッドです。
   */
  void reverse();

  /**
   * @brief モーターを停止させる
   *
   * モーターの回転を停止させるためのメソッドです。
   */
  void stop();

private:
  uint8_t pin1; ///< モーターの前進信号を制御するデジタルピン番号
  uint8_t pin2; ///< モーターの後進信号を制御するデジタルピン番号
};
