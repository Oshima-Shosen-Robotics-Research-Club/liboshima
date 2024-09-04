#include "TB67H450.h"
#include <Arduino.h>

// コンストラクタ: モーター制御用のピンを設定
TB67H450::TB67H450(int in1, int in2) : in1(in1), in2(in2) {
  // ピンを出力モードに設定
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

// モーターを制御する内部メソッド
void TB67H450::run(int pwmValue1, int pwmValue2) {
  // 指定されたピンに PWM 信号を出力
  analogWrite(in1, pwmValue1);
  analogWrite(in2, pwmValue2);
}

// 正転メソッド: モーターを前進させる
void TB67H450::forward() {
  // in1 に PWM 信号を出力し、in2 は LOW に設定
  run(255, 0); // 最大出力で前進
}

// 後転メソッド: モーターを後退させる
void TB67H450::reverse() {
  // in1 は LOW、in2 に PWM 信号を出力
  run(0, 255); // 最大出力で後退
}

// モーター停止メソッド: モーターを停止させる
void TB67H450::stop() {
  setSpeed(0); // 速度を 0 に設定
}

// モーターの速度を設定するメソッド
void TB67H450::setSpeed(float rate) {
  // スピードの範囲を -1.0 から 1.0 に制限
  rate = constrain(rate, -1.0, 1.0);
  int pwmValue = (int)(abs(rate) * 255); // 速度に応じた PWM 値を計算
  if (rate > 0) {
    run(pwmValue, 0); // 正転
  } else if (rate < 0) {
    run(0, pwmValue); // 後退
  } else {
    run(255, 255); // 停止
  }
}