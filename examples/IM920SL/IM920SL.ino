#include <SoftwareSerial.h>
#include <components/ims/IM920SL.h>

#define RX_PIN 0
#define TX_PIN 0

SoftwareSerial serial(RX_PIN, TX_PIN);
SerialPort serialPort(serial);
IM920SL im(serialPort);

void setup() {}

void loop() {
  // ImSender.inoから送信されたデータを受信する
  int data;
  im.send(data);
  im.receive(data);
}