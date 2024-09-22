#pragma once

#include "ImReceiver.h"
#include "ImSender.h"
#include "serials/SerialPort.h"

/**
 * @brief IM920SLを使用した通信を行うクラス
 *
 * `IM920SL` クラスは、IM920SLを使用して無線通信を行うための機能を提供します。
 * このクラスは、IM920SLを使用してデータの送受信を行うためのメソッドを提供します。
 */
class IM920SL : public ImReceiver, public ImSender {
public:
  /**
   * @brief コンストラクタ
   *
   * `ImReceiver` インスタンスと `ImSender` インスタンスを使用して
   * `IM920SL` クラスを初期化します。
   * @param serial 使用するシリアルポートの参照
   */
  IM920SL(SerialPort &serial);

  /**
   * @brief 通信を開始するメソッド
   *
   * このメソッドは、IM920SL通信モジュールを使用して通信を開始します。
   * 通信速度（ボーレート）を指定して通信を開始します。
   *
   * @param baudrate 通信速度（ボーレート）
   */
  void begin(unsigned long baudrate = 19200);

  uint8_t available();

private:
  SerialPort &serial; /**< 使用するシリアルポートの参照 */
};