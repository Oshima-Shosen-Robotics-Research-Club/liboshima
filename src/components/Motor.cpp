#include "Motor.h"
#include <Arduino.h> // Arduino プラットフォーム用

// コンストラクタ: モーター制御用のピンを設定
Motor::Motor(int pin1, int pin2) : pin1(pin1), pin2(pin2) {
  // ピンを出力モードに設定
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
}

// モーターを制御する内部メソッド
void Motor::run(int input1, int input2) {
  // 指定されたピンに信号を出力
  digitalWrite(pin1, input1);
  digitalWrite(pin2, input2);
}

// 正転メソッド: モーターを前進させる
void Motor::forward() {
  // pin1 を HIGH、pin2 を LOW にして正転
  run(HIGH, LOW);
}

// 後転メソッド: モーターを後退させる
void Motor::reverse() {
  // pin1 を LOW、pin2 を HIGH にして後転
  run(LOW, HIGH);
}

// モーター停止メソッド: モーターを停止させる
void Motor::stop() {
  // 両方のピンを HIGH にして停止
  run(HIGH, HIGH); // 両方のピンを HIGH にして停止
}