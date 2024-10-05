/**
 * @file Im920SL.h
 * @brief IM920SLモジュールを使用した無線通信クラスのヘッダファイル
 *
 * このファイルは、IM920SL無線モジュールを使って通信を行うためのクラス
 * `IM920SL` を提供します。このクラスを使用してデータの送受信や通信の初期化を
 * 行うことができます。
 */

#pragma once

#include "ImReceiver_private.h"
#include "ImSender_private.h"

/**
 * @class IM920SL
 * @brief IM920SLモジュールを使用して無線通信を行うクラス
 *
 * `IM920SL` クラスは、IM920SLモジュールを使用して無線通信を行います。
 * 主な機能として、通信の初期化、データの送受信、および受信データの管理を行います。
 * このクラスは `ImReceiver_private` と `ImSender_private`
 * の機能を継承しており、送受信に 必要なメソッドを提供します。
 */
class IM920SL : public ImReceiver_private, public ImSender_private {
public:
  /**
   * @brief IM920SLクラスのコンストラクタ
   *
   * IM920SL通信モジュールを使用するために、指定したシリアルポートを
   * 使用してクラスを初期化します。
   * @param serial
   * 使用するシリアルポートの参照。IM920SLモジュールと通信するために使用します。
   */
  IM920SL(SerialPort &serial);

  /**
   * @brief 通信を開始するメソッド
   *
   * 指定した通信速度（ボーレート）でIM920SLモジュールとの通信を開始します。
   * デフォルトのボーレートは19200bpsです。
   * @param baudrate 通信速度（ボーレート）。デフォルト値は19200。
   */
  void begin(unsigned long baudrate = 19200);

private:
  SerialPort &serial; /**< IM920SLモジュールと通信するためのシリアルポート */
};
