#include <SoftwareSerial.h>
#include <components/ims/ImSender.h>

#define RX_PIN 0
#define TX_PIN 0

ImSender imSender(0, 0);

void setup() {
  // 送信データを送信する
  int data = 123;
  imSender.send(data);
}

void loop() {}