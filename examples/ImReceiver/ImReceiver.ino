#include <components/ims/ImReceiver.h>

#define RX_PIN 4
#define TX_PIN 5

ImReceiver imReceiver(RX_PIN, TX_PIN);

void setup() {}

void loop() {
  // ImSender.inoから送信されたデータを受信する
  int data;
  if (imReceiver.receive(data)) {
    Serial.println(data);
  }
}