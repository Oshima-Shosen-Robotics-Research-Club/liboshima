#include "BD62193.h"
#include <Arduino.h>
#include <digitalWriteFast.h>

// コンストラクタ: モーター制御用のピンを設定
BD62193::BD62193(uint8_t inA_PIN, uint8_t inB_PIN, uint8_t pwm_PIN)
    : inA_PIN(inA_PIN), inB_PIN(inB_PIN), pwm_PIN(pwm_PIN),
      speedAdjustable(true) {
  // ピンを出力モードに設定
  pinModeFast(pwm_PIN, OUTPUT);
  pinModeFast(inA_PIN, OUTPUT);
  pinModeFast(inB_PIN, OUTPUT);
}

// コンストラクタ: モーター制御用のピンを設定 (PWMピンを使用しない場合)
BD62193::BD62193(uint8_t inA_PIN, uint8_t inB_PIN)
    : inA_PIN(inA_PIN), inB_PIN(inB_PIN), speedAdjustable(false) {
  // ピンを出力モードに設定
  pinModeFast(inA_PIN, OUTPUT);
  pinModeFast(inB_PIN, OUTPUT);
}

// モーターを制御する内部メソッド
void BD62193::run(bool inAState, bool inBState, uint8_t pwmValue) {
  // 指定されたピンに信号を出力
  analogWrite(pwm_PIN, pwmValue);
  digitalWriteFast(inA_PIN, inAState);
  digitalWriteFast(inB_PIN, inBState);
}

// モーターを制御する内部メソッド (PWMピンを使用しない場合)
void BD62193::run(bool inAState, bool inBState) {
  // 指定されたピンに信号を出力
  digitalWriteFast(inA_PIN, inAState);
  digitalWriteFast(inB_PIN, inBState);
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
  // スピードの範囲を -1.0 から 1.0 に制限
  rate = constrain(rate, -1.0, 1.0);

  if (rate == 0) {
    run(HIGH, HIGH); // 速度を 0 に設定
  } else if (!speedAdjustable) {
    run(rate > 0, rate < 0); // PWM を使用しない場合
  } else {
    uint8_t pwmValue = (uint8_t)(abs(rate) * 255); // 速度に応じた PWM 値を計算
    run(pwmValue, rate > 0, rate < 0);             // モーターを制御
  }
}