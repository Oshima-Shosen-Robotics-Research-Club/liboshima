/**
 * @file HS_485HB.h
 * @brief HS_485HBサーボモータのクラス定義
 *
 * このファイルには、HS_485HBサーボモータを制御するための
 * `HS_485HB` クラスが定義されています。このクラスは `Servo` クラスを
 * 継承し、サーボモータを制御する機能を提供します。
 */

#ifndef HS_485HB_H
#define HS_485HB_H

#include <Servo.h>

/**
 * @class HS_485HB
 * @brief HS_485HBサーボモータを制御するクラス
 *
 * `HS_485HB` クラスは、`Servo` クラスを継承し、HS_485HBサーボモータを
 * 制御するための機能を提供します。このクラスは、サーボモータの
 * ピンを設定するための `attach` メソッドを提供します。
 */
class HS_485HB : public Servo {
public:
  /**
   * @brief サーボモータのピンを設定するメソッド
   *
   * このメソッドは、サーボモータを制御するためのピンを設定します。
   *
   * @param pin サーボモータを接続するピンの番号
   */
  void attach(uint8_t pin);
};

#endif // HS_485HB_H
