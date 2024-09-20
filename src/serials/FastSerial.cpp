#include "FastSerial.h"

#if defined(__AVR_ATmega328P__)
FastSerial FSerial;

// 静的メンバ変数の定義
void (*FastSerial::user_onReceive)(void) = NULL;

void FastSerial::begin(unsigned long baudrate) {
  // ボーレートの設定
  UBRR0 = (F_CPU / 16 / baudrate - 1);

  // 送受信機能と割り込みを有効化
  UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);

  // データフォーマット設定（8ビットデータ、1ストップビット、パリティなし）
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);

  // 全割り込みを有効化
  sei();
}

size_t FastSerial::available() {
  // 受信データがあるかどうかをチェック
  return UCSR0A & _BV(RXC0);
}

char FastSerial::read() {
  // データが受信されるまで待つ
  while (!available())
    ;
  return UDR0;
}

size_t FastSerial::readBytesUntil(char terminator, char *buffer,
                                  size_t length) {
  size_t count = 0;
  while (count < length) {
    // データが受信されるまで待つ
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

size_t FastSerial::print(const char *str) {
  size_t count = 0;
  while (*str) {
    // 送信バッファが空になるまで待つ
    while (!(UCSR0A & _BV(UDRE0)))
      ;
    UDR0 = *str++;
    count++;
  }
  return count;
}

size_t FastSerial::println(const char *str) {
  size_t count = print(str);
  count += print("\r\n"); // 改行を追加
  return count;
}

void FastSerial::onReceive(void (*function)(void)) {
  user_onReceive = function;
}

// USART 受信完了割り込みハンドラ
ISR(USART_RX_vect) {
  if (FastSerial::user_onReceive) {
    FastSerial::user_onReceive(); // ユーザー定義のコールバック関数を呼び出す
  }
}
#endif
