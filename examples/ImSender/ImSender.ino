#include <components/ims/ImSender.h>

#define RX_PIN 2
#define TX_PIN 3

ImSender imSender(RX_PIN, TX_PIN);

void setup() {
  // 送信データを送信する
  int data = 123;
  imSender.send(data);
}

void loop() {}