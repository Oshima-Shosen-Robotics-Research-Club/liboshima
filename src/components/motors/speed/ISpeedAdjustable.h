/**
 * @file ISpeedAdjustable.h
 * @brief モータードライバの抽象基底クラス定義
 *
 * このファイルには、モータードライバのための抽象基底クラス `ISpeedAdjustable`
 * が 定義されています。`ISpeedAdjustable` クラスは、モーターの速度設定、前進、
 * 後退、停止のためのインターフェースを提供します。このクラスを継承する
 * クラスは、これらのメソッドを実装する必要があります。
 */

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>

/**
 * @class ISpeedAdjustable
 * @brief モーターを制御するための抽象基底クラス
 *
 * `ISpeedAdjustable` クラスは、モーターの速度設定や制御（前進、後退、停止）を
 * 行うための純粋仮想メソッドを定義した抽象基底クラスです。このクラスを
 * 継承するクラスは、これらのメソッドを実装する必要があります。
 */
class ISpeedAdjustable {
public:
  /**
   * @brief モーターの速度を設定するメソッド
   *
   * このメソッドは、モーターの速度を指定した割合で設定します。速度は
   * 0.0（停止）から1.0（最大速度）までの範囲で設定できます。
   *
   * @param rate モーターの速度割合（0.0〜1.0）
   */
  virtual void setSpeed(float rate) = 0;

  /**
   * @brief モーターを前進させるメソッド
   *
   * このメソッドは、モーターを前進させるための制御信号を出力します。
   */
  virtual void forward() = 0;

  /**
   * @brief モーターを後退させるメソッド
   *
   * このメソッドは、モーターを後退させるための制御信号を出力します。
   */
  virtual void reverse() = 0;

  /**
   * @brief モーターを停止させるメソッド
   *
   * このメソッドは、モーターを停止させるための制御信号を出力します。
   */
  virtual void stop() = 0;
};

#endif // MOTOR_DRIVER_H
