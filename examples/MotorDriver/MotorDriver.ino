#include <liboshima.h>

// ピンの定義
#define MOTOR1_PWM 0
#define MOTOR1_INA 0
#define MOTOR1_INB 0
#define MOTOR2_IN1 0
#define MOTOR2_IN2 0
#define MOTOR3_IN1 0
#define MOTOR3_IN2 0

// モータードライバのインスタンスを生成
BD62193 motor1(MOTOR1_PWM, MOTOR1_INA, MOTOR1_INB);
TB67H450 motor2(MOTOR2_IN1, MOTOR2_IN2);
NonSpeedAdjustable motor3(MOTOR3_IN1, MOTOR3_IN2);

void setup() {}

void loop() {
  motor1.setSpeed(1.0); // モーター1を正転
  delay(1000);
  motor1.setSpeed(0.5); // モーター1を半分の速度で正転
  delay(1000);
  motor1.setSpeed(0); // モーター1を停止
  delay(1000);
  motor1.setSpeed(-1.0); // モーター1を逆転
  delay(1000);

  motor2.setSpeed(1.0); // モーター2を正転
  delay(1000);
  motor2.setSpeed(0.5); // モーター2を半分の速度で正転
  delay(1000);
  motor2.setSpeed(0); // モーター2を停止
  delay(1000);
  motor2.setSpeed(-1.0); // モーター2を逆転
  delay(1000);

  motor3.forward(); // モーター3を正転
  delay(1000);
  motor3.stop(); // モーター3を停止
  delay(1000);
  motor3.reverse(); // モーター3を逆転
  delay(1000);
}