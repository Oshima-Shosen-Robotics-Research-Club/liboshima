#include <components/servos/HS_485HB.h>
#include <components/servos/MG90S.h>

MG90S servo1;
HS_485HB servo2;

void setup() {
  servo1.attach(0);
  servo2.attach(0);
}

void loop() {
  write(servo1, 0);
  delay(2000);
  write(servo1, 90);
  delay(2000);
  write(servo1, 180);
  delay(2000);

  write(servo2, 0);
  delay(2000);
  write(servo2, 90);
  delay(2000);
  write(servo2, 180);
  delay(2000);
}

void write(Servo &servo, int angle) { servo.write(angle); }