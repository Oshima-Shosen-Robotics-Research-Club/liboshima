#include <SoftwareSerial.h>
#include <components/ims/ImReceiver.h>

ImReceiver imReceiver(0, 0, false);
SoftwareSerial debugSerial(0, 0);

void setup() {}

void loop() {
  // ImSender.inoから送信されたデータを受信する
  int data;
  if (imReceiver.receive(data)) {
    debugSerial.println(data);
  }
}