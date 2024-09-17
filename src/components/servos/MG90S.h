/**
 * @file MG90S.h
 * @brief MG90Sサーボモータのクラス定義
 *
 * このファイルには、MG90Sサーボモータを制御するための
 * `MG90S` クラスが定義されています。このクラスは `Servo` クラスを
 * 継承し、サーボモータの制御機能を提供します。
 */

#ifndef MG90S_H
#define MG90S_H

#include <Servo.h>

/**
 * @class MG90S
 * @brief MG90Sサーボモータを制御するクラス
 *
 * `MG90S` クラスは、`Servo` クラスを継承し、MG90Sサーボモータを
 * 制御するための機能を提供します。このクラスでは、サーボモータの
 * 制御用のピンを設定するための `attach` メソッドを提供します。
 */
class MG90S : public Servo {
public:
  /**
   * @brief サーボモータのピンを設定するメソッド
   *
   * このメソッドは、サーボモータを制御するためのピンを指定して
   * 設定します。サーボモータを指定したピンに接続して制御を行います。
   *
   * @param pin サーボモータを接続するピンの番号
   */
  void attach(uint8_t pin);
};

#endif // MG90S_H
