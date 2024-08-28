#include "Motor.h"
#include <Arduino.h> // Arduino プラットフォーム用

// コンストラクタ
Motor::Motor(int pin1, int pin2) : pin1(pin1), pin2(pin2) {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
}

// モーターを制御する内部メソッド
void Motor::run(int input1, int input2) {
  digitalWrite(pin1, input1);
  digitalWrite(pin2, input2);
}

// 正転メソッド
void Motor::forward() {
  run(HIGH, LOW); // pin1 を HIGH、pin2 を LOW にして正転
}

// 後転メソッド
void Motor::reverse() {
  run(LOW, HIGH); // pin1 を LOW、pin2 を HIGH にして後転
}

// モーター停止メソッド
void Motor::stop() {
  run(HIGH, HIGH); // 両方のピンを HIGH にして停止
}
