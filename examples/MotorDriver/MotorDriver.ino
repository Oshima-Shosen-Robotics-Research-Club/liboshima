#include <components/motors/BD62193.h>
#include <components/motors/MotorDriver.h>
#include <components/motors/TB67H450.h>

// ピンの定義
#define MOTOR1_PWM 0
#define MOTOR1_INA 0
#define MOTOR1_INB 0
#define MOTOR2_IN1 0
#define MOTOR2_IN2 0

// モータードライバのインスタンスを生成
BD62193 motor1(MOTOR1_PWM, MOTOR1_INA, MOTOR1_INB);
TB67H450 motor2(MOTOR2_IN1, MOTOR2_IN2);

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