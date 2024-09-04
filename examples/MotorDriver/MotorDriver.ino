#include <components/motors/BD62193.h>
#include <components/motors/MotorDriver.h>
#include <components/motors/TB67H450.h>

// モータードライバのインスタンスを生成
BD62193 motor1(3, 4, 5);
TB67H450 motor2(6, 7);

void setup() {}

void loop() {
  forward(motor1);
  delay(2000);
  stop(motor1);
  delay(2000);
  reverse(motor1);
  delay(2000);
  stop(motor1);
  delay(2000);

  forward(motor2);
  delay(2000);
  stop(motor2);
  delay(2000);
  reverse(motor2);
  delay(2000);
  stop(motor2);
  delay(2000);
}

void forward(MotorDriver &motor) { motor.forward(); }

void reverse(MotorDriver &motor) { motor.reverse(); }

void stop(MotorDriver &motor) { motor.stop(); }