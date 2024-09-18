/**
 * @file TB67H450.h
 * @brief TB67H450モータードライバのクラス定義
 *
 * このファイルには、TB67H450モータードライバを制御するための
 * `TB67H450` クラスが定義されています。このクラスは `MotorDriver` クラスを
 * 継承し、モーターの前進、後退、停止、速度設定の機能を提供します。
 *
 * @note このクラスは、PWM信号を使用してモーターを制御します。
 */

#ifndef TB67H450_H
#define TB67H450_H

#include "MotorDriver.h"

/**
 * @class TB67H450
 * @brief TB67H450モータードライバを制御するクラス
 *
 * `TB67H450` クラスは、TB67H450モータードライバを使用してモーターを
 * 制御するための機能を提供します。PWM信号を利用してモーターの速度と
 * 方向を制御します。
 */
class TB67H450 : public MotorDriver {
private:
  uint8_t in1; /**< PWM信号を出力するピンの番号1 */
  uint8_t in2; /**< PWM信号を出力するピンの番号2 */

  /**
   * @brief モーターを制御する内部メソッド
   *
   * このメソッドは、指定されたPWM値に基づいてモーターを制御します。
   *
   * @param analogueValue1 PWM信号の値1（0〜255）
   * @param analogueValue2 PWM信号の値2（0〜255）
   */
  void runAnalogue(uint8_t analogueValue1, uint8_t analogueValue2);

  /**
   * @brief モーターを制御する内部メソッド
   *
   * このメソッドは、指定されたDigital値に基づいてモーターを制御します。
   *
   * @param digitalValue1 Digital信号の値1（HIGH または LOW）
   * @param digitalValue2 Digital信号の値2（HIGH または LOW）
   */
  void runDigital(bool digitalValue1, bool digitalValue2);

public:
  /**
   * @brief コンストラクタ
   *
   * モーターを制御するためのピン番号を初期化します。
   *
   * @param in1 PWM信号を出力するピンの番号1
   * @param in2 PWM信号を出力するピンの番号2
   */
  TB67H450(uint8_t in1, uint8_t in2);

  /**
   * @brief モーターを前進させるメソッド
   *
   * このメソッドは、モーターを前進させるための制御信号を出力します。
   */
  void forward() override;

  /**
   * @brief モーターを後退させるメソッド
   *
   * このメソッドは、モーターを後退させるための制御信号を出力します。
   */
  void reverse() override;

  /**
   * @brief モーターを停止させるメソッド
   *
   * このメソッドは、モーターを停止させるための制御信号を出力します。
   */
  void stop() override;

  /**
   * @brief モーターの速度を設定するメソッド
   *
   * このメソッドは、モーターの速度を指定した割合で設定します。速度は
   * 0.0（停止）から1.0（最大速度）までの範囲で設定できます。
   *
   * @param rate モーターの速度割合（0.0〜1.0）
   */
  void setSpeed(float rate) override;
};

#endif // TB67H450_H
