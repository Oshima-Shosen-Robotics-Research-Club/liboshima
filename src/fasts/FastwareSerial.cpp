#include "FastwareSerial.h"
#include <avr/interrupt.h>
#include <fasts/Converter.h>

// グローバルインスタンスの定義
FastwareSerial FastSerial;

// シリアル通信を開始する関数
void FastwareSerial::begin(unsigned long baudrate) {
#if defined(__AVR_ATmega328P__)
  // ボーレートの設定
  UBRR0 = (F_CPU / 16 / baudrate - 1);
  // 受信、送信、受信割り込みの有効化
  UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);
  // フレームフォーマットの設定: 8データビット、1ストップビット
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
  // グローバル割り込みの有効化
  sei();
#endif
}

// 受信バッファにデータがあるか確認する関数
uint8_t FastwareSerial::available() {
#if defined(__AVR_ATmega328P__)
  // 受信完了フラグをチェック
  return UCSR0A & _BV(RXC0);
#endif
}

// 1バイトのデータを読み取る関数
char FastwareSerial::read() {
#if defined(__AVR_ATmega328P__)
  // データが受信されるまで待機
  while (!available())
    ;
  // 受信データを返す
  return UDR0;
#endif
}

// 指定された終端文字が現れるまでデータを読み取る関数
uint8_t FastwareSerial::readBytesUntil(char terminator, char *buffer, uint8_t length) {
  uint8_t count = 0;
  while (count < length) {
    // データが受信されるまで待機
    while (!available())
      ;
    buffer[count] = read();
    if (buffer[count] == terminator) {
      break;
    }
    count++;
  }
  return count;
}

// 1バイトのデータを書き込む関数
uint8_t FastwareSerial::write(uint8_t data) {
#if defined(__AVR_ATmega328P__)
  // 送信バッファが空になるまで待機
  while (!(UCSR0A & _BV(UDRE0)))
    ;
  // データを送信
  UDR0 = data;
  return 1;
#endif
}

// 文字列を送信する関数
uint8_t FastwareSerial::print(const char *str) {
  uint8_t count = 0;
  while (*str) {
    write(*str++);
    count++;
  }
  return count;
}

// 文字列を送信し、改行を追加する関数
uint8_t FastwareSerial::println(const char *str) {
  uint8_t count = print(str);
  count += println();
  return count;
}

// 改行を送信する関数
uint8_t FastwareSerial::println() { return print("\r\n"); }

// 1バイトの値を16進数で送信する関数
uint8_t FastwareSerial::print(uint8_t value) {
  uint8_t count = 0;
  char buffer[3]; // 1バイト分の16進数表現に必要な2文字 + null文字
  Converter::toHex(&value, 1, buffer);
  count += print(buffer);
  return count;
}

// 受信割り込み時に呼び出されるユーザー定義関数を設定する関数
void FastwareSerial::onReceive(void (*function)(void)) {
  user_onReceive = function;
}

// 受信割り込みハンドラ
#if defined(__AVR_ATmega328P__) && defined(USE_FASTWARE_SERIAL)
ISR(USART_RX_vect) {
  if (FastSerial.user_onReceive) {
    FastSerial.user_onReceive();
  }
}
#endif