/**
 * @file BD62193.h
 * @brief BD62193モータードライバのクラス定義
 *
 * このファイルには、BD62193モータードライバを制御するための
 * `BD62193` クラスが定義されています。このクラスは `MotorDriver` クラスを
 * 継承し、モーターの前進、後退、停止、速度設定の機能を提供します。
 *
 * @note このクラスは、PWM制御をサポートしており、モーターの制御に
 *       使用されるピンの設定を行います。
 */

#ifndef BD62193_H
#define BD62193_H

#include "MotorDriver.h"

/**
 * @class BD62193
 * @brief BD62193モータードライバを制御するクラス
 *
 * `BD62193` クラスは、BD62193モータードライバを使用してモーターを
 * 制御するための機能を提供します。PWMピンを使用するかどうかに
 * 依存して、モーターの前進、後退、停止、速度設定を行います。
 */
class BD62193 : public MotorDriver {
private:
  uint8_t pwmPin;    /**< PWM信号を出力するピンの番号 */
  uint8_t inAPin;    /**< モーターの入力Aピンの番号 */
  uint8_t inBPin;    /**< モーターの入力Bピンの番号 */
  bool isPWM = true; /**< PWMピンを使用するかどうかのフラグ */

  /**
   * @brief モーターを制御する内部メソッド
   *
   * このメソッドは、指定されたPWM値と入力ピンの状態に基づいて
   * モーターを制御します。
   *
   * @param pwmValue PWM信号の値（0〜255）
   * @param inAState 入力Aピンの状態（HIGH または LOW）
   * @param inBState 入力Bピンの状態（HIGH または LOW）
   */
  void run(uint8_t pwmValue, bool inAState, bool inBState);

public:
  /**
   * @brief コンストラクタ (PWMピンを使用する場合)
   *
   * PWMピンを使用してモーターを制御するためのコンストラクタです。
   *
   * @param pwm PWM信号を出力するピンの番号
   * @param inA モーターの入力Aピンの番号
   * @param inB モーターの入力Bピンの番号
   */
  BD62193(uint8_t pwm, uint8_t inA, uint8_t inB);

  /**
   * @brief コンストラクタ (PWMピンを使用しない場合)
   *
   * PWMピンを使用せずにモーターを制御するためのコンストラクタです。
   *
   * @param inA モーターの入力Aピンの番号
   * @param inB モーターの入力Bピンの番号
   */
  BD62193(uint8_t inA, uint8_t inB);

  /**
   * @brief モーターを前進させるメソッド
   *
   * モーターを前進させるための制御信号を出力します。
   */
  void forward() override;

  /**
   * @brief モーターを後退させるメソッド
   *
   * モーターを後退させるための制御信号を出力します。
   */
  void reverse() override;

  /**
   * @brief モーターを停止させるメソッド
   *
   * モーターを停止させるための制御信号を出力します。
   */
  void stop() override;

  /**
   * @brief モーターの速度を設定するメソッド
   *
   * モーターの速度を指定した割合で設定します。速度は0.0（停止）から
   * 1.0（最大速度）までの範囲で設定できます。
   *
   * @param rate モーターの速度割合（0.0〜1.0）
   */
  void setSpeed(float rate) override;
};

#endif // BD62193_H
