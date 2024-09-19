#include "FastSerial.h"

#if defined(__AVR_ATmega328P__)
void FastSerial::begin(unsigned long baudrate) {
  // USART初期化
  UBRR0 = 25; // ボーレート19200//51:9600
  UCSR0B = 0x80;
  UCSR0C = 0x06;

  // USARTスタート
  UCSR0B |= _BV(RXEN0) | _BV(TXEN0);

  // 全割込み許可
  sei();
}

size_t FastSerial::available() { return UCSR0A & _BV(RXC0); }

char FastSerial::read() {
  while (!available())
    return UDR0;
}

size_t FastSerial::readBytesUntil(char terminator, char *buffer,
                                  size_t length) {
  size_t count = 0;
  while (count < length) {
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
    while (!(UCSR0A & _BV(UDRE0)))
      ;
    UDR0 = *str++;
    count++;
  }
  return count;
}

size_t FastSerial::println(const char *str) {
  size_t count = print(str);
  count += print("\r\n");
  return count;
}

void FastSerial::onReceive(void (*function)(void)) {
  attachInterrupt(USART_RX_vect, function, RXCIE0);
}
#endif