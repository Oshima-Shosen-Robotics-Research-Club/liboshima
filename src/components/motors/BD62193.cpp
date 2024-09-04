#include "BD62193.h"

// コンストラクタ: モーター制御用のピンを設定
BD62193::BD62193(int pwm, int inA, int inB)
    : pwmPin(pwm), inAPin(inA), inBPin(inB) {
  // ピンを出力モードに設定
  pinMode(pwmPin, OUTPUT);
  pinMode(inAPin, OUTPUT);
  pinMode(inBPin, OUTPUT);
}

// モーターを制御する内部メソッド
void BD62193::run(int pwmValue, bool inAState, bool inBState) {
  // 指定されたピンに信号を出力
  analogWrite(pwmPin, pwmValue);
  digitalWrite(inAPin, inAState ? HIGH : LOW);
  digitalWrite(inBPin, inBState ? HIGH : LOW);
}

// 正転メソッド: モーターを前進させる
void BD62193::forward() {
  // inAPin に PWM 信号を出力し、inBPin は LOW に設定
  run(255, HIGH, LOW); // 最大出力で前進
}

// 後転メソッド: モーターを後退させる
void BD62193::reverse() {
  // inAPin は LOW、inBPin に PWM 信号を出力
  run(255, LOW, HIGH); // 最大出力で後退
}

// モーター停止メソッド: モーターを停止させる
void BD62193::stop() {
  run(0, LOW, LOW); // 停止設定
}

// モーターの速度を設定するメソッド
void BD62193::setSpeed(float rate) {
  // スピードの範囲を -1.0 から 1.0 に制限
  rate = constrain(rate, -1.0, 1.0);
  int pwmValue = (int)(abs(rate) * 255); // 速度に応じた PWM 値を計算

  if (rate > 0) {
    run(pwmValue, HIGH, LOW); // 正転設定
  } else if (rate < 0) {
    run(pwmValue, LOW, HIGH); // 後退設定
  } else {
    run(0, LOW, LOW); // 停止設定
  }
}