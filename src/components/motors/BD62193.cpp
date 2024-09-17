#include "BD62193.h"

// コンストラクタ: モーター制御用のピンを設定
BD62193::BD62193(uint8_t pwm, uint8_t inA, uint8_t inB)
    : pwmPin(pwm), inAPin(inA), inBPin(inB) {
  // ピンを出力モードに設定
  pinMode(pwmPin, OUTPUT);
  pinMode(inAPin, OUTPUT);
  pinMode(inBPin, OUTPUT);
}

BD62193::BD62193(uint8_t inA, uint8_t inB)
    : inAPin(inA), inBPin(inB), isPWM(false) {
  // ピンを出力モードに設定
  pinMode(inAPin, OUTPUT);
  pinMode(inBPin, OUTPUT);
}

// モーターを制御する内部メソッド
void BD62193::run(uint8_t pwmValue, bool inAState, bool inBState) {
  // 指定されたピンに信号を出力
  if (isPWM)
    analogWrite(pwmPin, pwmValue);
  digitalWrite(inAPin, inAState);
  digitalWrite(inBPin, inBState);
}

// 正転メソッド: モーターを前進させる
void BD62193::forward() {
  setSpeed(1.0); // 最大出力で前進
}

// 後転メソッド: モーターを後退させる
void BD62193::reverse() {
  setSpeed(-1.0); // 最大出力で後退
}

// モーター停止メソッド: モーターを停止させる
void BD62193::stop() {
  setSpeed(0); // 速度を 0 に設定
}

// モーターの速度を設定するメソッド
void BD62193::setSpeed(float rate) {

  if (!isPWM) {
    if (rate > 0) {
      rate = 1.0; // 正転設定
    } else if (rate < 0) {
      rate = -1.0; // 後退設定
    } else {
      rate = 0; // 停止設定
    }
  }

  // スピードの範囲を -1.0 から 1.0 に制限
  rate = constrain(rate, -1.0, 1.0);
  uint8_t pwmValue = (uint8_t)(abs(rate) * 255); // 速度に応じた PWM 値を計算

  if (rate > 0) {
    run(pwmValue, HIGH, LOW); // 正転設定
  } else if (rate < 0) {
    run(pwmValue, LOW, HIGH); // 後退設定
  } else {
    run(0, HIGH, HIGH); // 停止設定
  }
}