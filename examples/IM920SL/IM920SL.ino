// Arduino IDEの場合は "#include <liboshima.h>" としてください。
#include <components/ims/IM920SL.h>

#define RX_PIN 0
#define TX_PIN 0

SoftwareSerial serial(RX_PIN, TX_PIN);
IM920SL im(serial);

void setup() {}

void loop() {
  // ImSender.inoから送信されたデータを受信する
  int data;
  im.send(data);
  im.receive(data);
}