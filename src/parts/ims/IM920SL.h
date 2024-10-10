/**
 * @file IM920SL.h
 *
 * @brief IM920SLモジュールを使用してデータの送受信を行うためのクラス定義
 *
 * このファイルには、IM920SLモジュールを使用してデータの送受信を行うための
 * `IM920SL` クラスが定義されています。
 * このクラスは、IM920SLモジュールを使用してデータの送受信を行うための
 * 機能を提供します。
 */
#pragma once

#include "ImReceiver.h"
#include "ImSender.h"

/**
 * @brief IM920SLクラス
 *
 * このクラスは、IM920SLモジュールを使用してデータの送受信を行うためのクラスです。
 * SerialTypeとLoggerTypeをテンプレート引数として受け取ります。
 *
 * @tparam SerialType シリアル通信の型
 * @tparam LoggerType ロガーの型（デフォルトはDebugLogger<SerialType>*）
 */
template <typename SerialType, typename LoggerType = void>
class IM920SL : public ImReceiver<SerialType, LoggerType>,
                public ImSender<SerialType, LoggerType> {
public:
  /**
   * @brief コンストラクタ
   *
   * @param serial シリアル通信オブジェクト
   * @param logger ロガーオブジェクト（デフォルトはnullptr）
   */
  IM920SL(SerialType &serial, LoggerType *logger = nullptr)
      : ImReceiver<SerialType, LoggerType>(serial, logger),
        ImSender<SerialType, LoggerType>(serial, logger), serial(serial) {
    static_assert(!IsSame<DebugLogger<SerialType>, LoggerType>::value,
                  "シリアル通信がロガーと競合しています");
  }

  /**
   * @brief シリアル通信を開始する
   *
   * @param baudrate ボーレート（デフォルトは19200）
   */
  void begin(unsigned long baudrate = 19200) { serial.begin(baudrate); }

  /**
   * @brief 利用可能なデータのバイト数を取得する
   *
   * @return 利用可能なデータのバイト数
   */
  uint8_t available() { return serial.available(); }

private:
  SerialType &serial; ///< シリアル通信オブジェクトの参照
};