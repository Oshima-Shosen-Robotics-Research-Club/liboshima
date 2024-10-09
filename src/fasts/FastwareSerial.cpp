#include "FastwareSerial.h"
#include <avr/interrupt.h>
#include <utils/Converter.h>

FastwareSerial FastSerial;

void FastwareSerial::begin(unsigned long baudrate) {
#if defined(__AVR_ATmega328P__)
  UBRR0 = (F_CPU / 16 / baudrate - 1);
  UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
  sei();
#endif
}

uint8_t FastwareSerial::available() {
#if defined(__AVR_ATmega328P__)
  return UCSR0A & _BV(RXC0);
#endif
}

char FastwareSerial::read() {
#if defined(__AVR_ATmega328P__)
  while (!available())
    ;
  return UDR0;
#endif
}

uint8_t FastwareSerial::readBytesUntil(char terminator, char *buffer,
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

uint8_t FastwareSerial::write(uint8_t data) {
#if defined(__AVR_ATmega328P__)
  while (!(UCSR0A & _BV(UDRE0)))
    ;
  UDR0 = data;
  return 1;
#endif
}

uint8_t FastwareSerial::print(const char *str) {
  uint8_t count = 0;
  while (*str) {
    write(*str++);
    count++;
  }
  return count;
}

uint8_t FastwareSerial::println(const char *str) {
  uint8_t count = print(str);
  count += println();
  return count;
}

uint8_t FastwareSerial::println() { return print("\r\n"); }

uint8_t FastwareSerial::print(uint8_t value) {
  uint8_t count = 0;
  char buffer[3]; // 1byte分の16進数表現に必要な2文字 + null文字
  Converter::toHex(&value, 1, buffer);
  count += print(buffer);
  return count;
}

void FastwareSerial::onReceive(void (*function)(void)) {
  user_onReceive = function;
}

// please define this macro yourself (todo: fix this system)
#if defined(__AVR_ATmega328P__) && defined(USE_FASTWARE_SERIAL)
ISR(USART_RX_vect) {
  if (FastSerial.user_onReceive) {
    FastSerial.user_onReceive();
  }
}
#endif