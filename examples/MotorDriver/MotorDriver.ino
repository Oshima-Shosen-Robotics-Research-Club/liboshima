#include <liboshima.h> // モータードライバ制御ライブラリをインクルード

// ピンの定義
#define MOTOR1_PWM 0 // モーター1のPWMピン
#define MOTOR1_INA 0 // モーター1の入力Aピン
#define MOTOR1_INB 0 // モーター1の入力Bピン
#define MOTOR2_IN1 0 // モーター2の入力1ピン
#define MOTOR2_IN2 0 // モーター2の入力2ピン
#define MOTOR3_IN1 0 // モーター3の入力1ピン
#define MOTOR3_IN2 0 // モーター3の入力2ピン

// モータードライバのインスタンスを生成
// BD62193: モーター1用のドライバ
// TB67H450: モーター2用のドライバ
// NonSpeedAdjustable: モーター3用のドライバ（速度調整不可）
BD62193 motor1(MOTOR1_PWM, MOTOR1_INA, MOTOR1_INB);
TB67H450 motor2(MOTOR2_IN1, MOTOR2_IN2);
NonSpeedAdjustable motor3(MOTOR3_IN1, MOTOR3_IN2);

void setup() {
  // 初期化処理は特に必要ないため、setup関数内では何もしない
}

void loop() {
  // モーター1を最大速度で正転
  motor1.setSpeed(1.0);
  delay(1000); // 1秒間待機

  // モーター1を半分の速度で正転
  motor1.setSpeed(0.5);
  delay(1000); // 1秒間待機

  // モーター1を停止
  motor1.setSpeed(0);
  delay(1000); // 1秒間待機

  // モーター1を最大速度で逆転
  motor1.setSpeed(-1.0);
  delay(1000); // 1秒間待機

  // モーター2を最大速度で正転
  motor2.setSpeed(1.0);
  delay(1000); // 1秒間待機

  // モーター2を半分の速度で正転
  motor2.setSpeed(0.5);
  delay(1000); // 1秒間待機

  // モーター2を停止
  motor2.setSpeed(0);
  delay(1000); // 1秒間待機

  // モーター2を最大速度で逆転
  motor2.setSpeed(-1.0);
  delay(1000); // 1秒間待機

  // モーター3を正転
  motor3.forward();
  delay(1000); // 1秒間待機

  // モーター3を停止
  motor3.stop();
  delay(1000); // 1秒間待機

  // モーター3を逆転
  motor3.reverse();
  delay(1000); // 1秒間待機
}