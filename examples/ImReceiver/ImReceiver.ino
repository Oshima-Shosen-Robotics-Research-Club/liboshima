#include <components/ims/ImReceiver.h>
#include <SoftwareSerial.h>

ImReceiver imReceiver(Serial);
SoftwareSerial debugSerial(0, 0);

void setup() {}

void loop() {
  // ImSender.inoから送信されたデータを受信する
  int data;
  if (imReceiver.receive(data)) {
    debugSerial.println(data);
  }
}