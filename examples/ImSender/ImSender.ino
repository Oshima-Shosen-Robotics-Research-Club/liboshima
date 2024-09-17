#include <SoftwareSerial.h>
#include <components/ims/ImSender.h>

#define RX_PIN 0
#define TX_PIN 0

SoftwareSerial serial(RX_PIN, TX_PIN);
ImSender imSender(serial);

void setup() {
  // 送信データを送信する
  int data = 123;
  if (imSender.send(data) == ImSender::ErrorCode::SUCCESS) {
    Serial.println("Data sent successfully");
  } else {
    Serial.println("Failed to send data");
  }
}

void loop() {}