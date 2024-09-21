#include "FastSerial.h"
#include <utils/Converter.h>

FastSerial FSerial;

#if defined(__AVR_ATmega328P__)
void (*FastSerial::user_onReceive)(void) = NULL;

void FastSerial::begin(unsigned long baudrate) {
  UBRR0 = (F_CPU / 16 / baudrate - 1);
  UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
  sei();
}

uint8_t FastSerial::available() { return UCSR0A & _BV(RXC0); }

char FastSerial::read() {
  while (!available())
    ;
  return UDR0;
}

uint8_t FastSerial::readBytesUntil(char terminator, char *buffer,
                                   uint8_t length) {
  uint8_t count = 0;
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

uint8_t FastSerial::write(uint8_t data) {
  while (!(UCSR0A & _BV(UDRE0)))
    ;
  UDR0 = data;
  return 1;
}

uint8_t FastSerial::print(const char *str) {
  uint8_t count = 0;
  while (*str) {
    write(*str++);
    count++;
  }
  return count;
}

uint8_t FastSerial::println(const char *str) {
  uint8_t count = print(str);
  count += println();
  return count;
}

uint8_t FastSerial::println() { return print("\r\n"); }

uint8_t FastSerial::print(uint8_t value) {
  uint8_t count = 0;
  char buffer[3]; // 1byte分の16進数表現に必要な2文字 + null文字
  Converter::toHex(&value, 1, buffer);
  count += print(buffer);
  return count;
}

void FastSerial::onReceive(void (*function)(void)) {
  user_onReceive = function;
}

ISR(USART_RX_vect) {
  if (FastSerial::user_onReceive) {
    FastSerial::user_onReceive();
  }
}
#endif
