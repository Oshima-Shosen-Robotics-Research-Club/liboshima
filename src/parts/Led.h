#pragma once

#include <Arduino.h>
#include <digitalWriteFast.h>
#include <stdint.h>

/**
 * @brief LEDを制御するためのクラス
 *
 * このクラスは、指定されたピンに接続されたLEDを制御するための機能を提供します。
 * LEDのオン、オフ、トグル（状態の切り替え）を行うことができます。
 */
class Led {
public:
  /**
   * @brief コンストラクタ
   *
   * 指定されたピンを出力モードに設定します。
   *
   * @param pin LEDが接続されているピン番号
   */
  Led(uint8_t pin) : pin(pin) {
    // 指定されたピンを出力モードに設定
    pinModeFast(pin, OUTPUT);
  }

  /**
   * @brief LEDを点灯させる
   *
   * 指定されたピンにHIGH信号を送ることでLEDを点灯させます。
   */
  void on() {
    // LEDを点灯させるためにピンにHIGH信号を送る
    digitalWriteFast(pin, HIGH);
  }

  /**
   * @brief LEDを消灯させる
   *
   * 指定されたピンにLOW信号を送ることでLEDを消灯させます。
   */
  void off() {
    // LEDを消灯させるためにピンにLOW信号を送る
    digitalWriteFast(pin, LOW);
  }

  /**
   * @brief LEDの状態を切り替える
   *
   * 現在のLEDの状態を読み取り、それを反転させることでLEDの状態を切り替えます。
   * 点灯している場合は消灯し、消灯している場合は点灯します。
   */
  void toggle() {
    // 現在のLEDの状態を読み取り、それを反転させる
    digitalWriteFast(pin, !digitalReadFast(pin));
  }

private:
  uint8_t pin; ///< LEDが接続されているピン番号
};