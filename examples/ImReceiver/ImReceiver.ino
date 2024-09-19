#include <SoftwareSerial.h>
#include <components/ims/ImReceiver.h>

#define RX_PIN 0
#define TX_PIN 0

SoftwareSerial serial(RX_PIN, TX_PIN);
ImReceiver imReceiver(serial);

void setup() {}

void loop() {
  // ImSender.inoから送信されたデータを受信する
  int data;
  imReceiver.receive(data);
}