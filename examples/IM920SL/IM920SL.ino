#include <SoftwareSerial.h>
#include <liboshima.h>

#define RX_PIN 0
#define TX_PIN 0

SoftwareSerial serial(RX_PIN, TX_PIN);
IM920SL<SoftwareSerial> im(serial);

void setup() {}

void loop() {
  // ImSender.inoから送信されたデータを受信する
  int data;
  im.send(data, ImSender<void>::WaitMode::CAREER_SENSE);
  im.receive(data, ImReceiver<void>::Mode::WAIT);
}