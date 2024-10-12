#include "NonSpeedAdjustable.h"
#include <digitalWriteFast.h>

// コンストラクタ: モーター制御用のピンを設定
NonSpeedAdjustable::NonSpeedAdjustable(uint8_t pin1, uint8_t pin2)
    : pin1(pin1), pin2(pin2) {
  // ピンを出力モードに設定
  pinModeFast(pin1, OUTPUT);
  pinModeFast(pin2, OUTPUT);
}

// 正転メソッド: モーターを前進させる
void NonSpeedAdjustable::forward() {
  // pin1 を HIGH、pin2 を LOW に設定してモーターを前進
  digitalWriteFast(pin1, HIGH);
  digitalWriteFast(pin2, LOW);
}

// 後転メソッド: モーターを後退させる
void NonSpeedAdjustable::reverse() {
  // pin1 を LOW、pin2 を HIGH に設定してモーターを後退
  digitalWriteFast(pin1, LOW);
  digitalWriteFast(pin2, HIGH);
}

// モーター停止メソッド: モーターを停止させる
void NonSpeedAdjustable::stop() {
  // pin1 と pin2 を両方 HIGH に設定してモーターを停止
  digitalWriteFast(pin1, HIGH);
  digitalWriteFast(pin2, HIGH);
}