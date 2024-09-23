/**
 * @file SerialPort.h
 * @brief シリアル通信を抽象化するクラス SerialPort の宣言
 *
 * `SerialPort`
 * クラスは、複数のシリアル通信実装（`HardwareSerial`、`SoftwareSerial`、
 * `FastwareSerial`）を抽象化して、統一されたインターフェースを提供します。これにより、
 * ハードウェアやソフトウェアのシリアル通信を柔軟に切り替え可能です。
 */

#pragma once

#if defined(USE_FASTWARE_SERIAL)
#include "FastwareSerial.h"
#else
#include <HardwareSerial.h>
#endif
#include <SoftwareSerial.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @class SerialPort
 * @brief シリアル通信を抽象化するクラス
 *
 * `SerialPort`
 * クラスは、異なるシリアル通信オブジェクト（`HardwareSerial`、`SoftwareSerial`、
 * または
 * `FastwareSerial`）を統一されたインターフェースで扱えるようにするための抽象化クラスです。
 */
class SerialPort {
public:
  /**
   * @brief FastwareSerial 用のコンストラクタ
   *
   * `FastwareSerial` オブジェクトを使用するためのコンストラクタです。
   *
   * @param serial 使用する `FastwareSerial` オブジェクトの参照
   */
#if defined(USE_FASTWARE_SERIAL)
  SerialPort(FastwareSerial &serial);
#else
  /**
   * @brief HardwareSerial 用のコンストラクタ
   *
   * `HardwareSerial` オブジェクトを使用するためのコンストラクタです。
   *
   * @param serial 使用する `HardwareSerial` オブジェクトの参照
   */
  SerialPort(HardwareSerial &serial);
#endif

  /**
   * @brief SoftwareSerial 用のコンストラクタ
   *
   * `SoftwareSerial` オブジェクトを使用するためのコンストラクタです。
   *
   * @param serial 使用する `SoftwareSerial` オブジェクトの参照
   */
  SerialPort(SoftwareSerial &serial);

  /**
   * @brief シリアル通信を開始します。
   *
   * 選択されたシリアルオブジェクト（`HardwareSerial`、`SoftwareSerial`、`FastwareSerial`）
   * で通信を開始します。
   *
   * @param baudrate 通信速度（ボーレート）
   */
  void begin(unsigned long baudrate);

  /**
   * @brief 受信可能なバイト数を取得します。
   *
   * 受信バッファ内にある利用可能なデータのバイト数を返します。
   *
   * @return 利用可能なデータのバイト数
   */
  uint8_t available();

  /**
   * @brief 1バイトのデータを読み取ります。
   *
   * 受信バッファから1バイトのデータを読み取ります。
   *
   * @return 読み取られたデータ（1バイト）
   */
  char read();

  /**
   * @brief 指定した終端文字までのデータを読み取り、バッファに格納します。
   *
   * 指定した終端文字に達するか、バッファがいっぱいになるまでデータを読み取ります。
   *
   * @param terminator 読み取りを終了する終端文字
   * @param buffer 読み取ったデータを格納するバッファ
   * @param length バッファの長さ（最大読み取りバイト数）
   * @return 実際に読み取られたバイト数
   */
  uint8_t readBytesUntil(char terminator, char *buffer, uint8_t length);

  /**
   * @brief 文字列を送信します。
   *
   * 指定した文字列をシリアル通信で送信します。
   *
   * @param str 送信する文字列
   * @return 送信に成功したバイト数
   */
  uint8_t print(const char *str);

  /**
   * @brief 数値データを送信します。
   *
   * 指定した数値データをシリアル通信で送信します。
   *
   * @param value 送信する数値データ
   * @return 送信に成功したバイト数
   */
  uint8_t print(int value);

  /**
   * @brief 文字列を送信し、改行を付加します。
   *
   * 指定した文字列を送信した後、改行を付加します。
   *
   * @param str 送信する文字列
   * @return 送信に成功したバイト数
   */
  uint8_t println(const char *str);

  /**
   * @brief 改行のみを送信します。
   *
   * 改行（`\n`）のみをシリアル通信で送信します。
   *
   * @return 送信に成功したバイト数
   */
  uint8_t println();

private:
  // 基本シリアルオブジェクトへのポインタ
#if defined(USE_FASTWARE_SERIAL)
  FastwareSerial *fwSerial; /**< FastwareSerial オブジェクトのポインタ */
  FastwareSerial *hwSerial; /**< dummy */
#else
  HardwareSerial *hwSerial; /**< HardwareSerial オブジェクトのポインタ */
  HardwareSerial *fwSerial; /**< dummy */
#endif
  SoftwareSerial *swSerial; /**< SoftwareSerial オブジェクトのポインタ */

  /**
   * @brief 使用中のシリアル通信の種類を示す列挙型
   *
   * `NONE`: シリアル通信が設定されていない。
   * `HARDWARE`: ハードウェアシリアルを使用中。
   * `SOFTWARE`: ソフトウェアシリアルを使用中。
   * `FASTWARE`: Fastwareシリアルを使用中。
   */
  enum SerialType { NONE, HARDWARE, SOFTWARE, FASTWARE } serialType;
};
