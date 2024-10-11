#pragma once

#include <Arduino.h>
#include <digitalWriteFast.h>
#include <stdint.h>

/**
 * @class Button
 * @brief ボタン入力を管理するクラス
 *
 * このクラスは、指定されたピンに接続されたボタンの状態を管理します。
 * ボタンが押されたかどうかを判定するためのメソッドを提供します。
 */
class Button {
public:
  /**
   * @brief コンストラクタ
   *
   * 指定されたピン番号を使用してButtonクラスのインスタンスを初期化します。
   * ピンは内部プルアップ抵抗を使用する入力モードに設定されます。
   *
   * @param pin ボタンが接続されているデジタルピン番号
   */
  Button(uint8_t pin) : pin(pin) { pinModeFast(pin, INPUT_PULLUP); }

  /**
   * @brief ボタンが押されているかどうかを判定するメソッド
   *
   * このメソッドは、ボタンが押されているかどうかを判定します。
   * ボタンが押されている場合は true を、押されていない場合は false を返します。
   *
   * @return ボタンが押されている場合は true、押されていない場合は false
   */
  bool isPressed() { return digitalReadFast(pin) == LOW; }

private:
  uint8_t pin; ///< ボタンが接続されているデジタルピン番号
};