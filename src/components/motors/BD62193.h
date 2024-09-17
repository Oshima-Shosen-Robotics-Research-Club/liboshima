#ifndef BD62193_H
#define BD62193_H

#include "MotorDriver.h"

class BD62193 : public MotorDriver {
private:
  uint8_t pwmPin;
  uint8_t inAPin;
  uint8_t inBPin;
  bool isPWM = true; // PWM ピンを使うかどうかのフラグ
  void run(uint8_t pwmValue, bool inAState,
           bool inBState); // モーターを制御する内部メソッド

public:
  BD62193(uint8_t pwm, uint8_t inA,
          uint8_t inB); // コンストラクタ、ピン番号を初期化
  BD62193(uint8_t inA, uint8_t inB); // コンストラクタ、PWM ピンを使わない場合
  void forward() override; // モーターを前進させるメソッド
  void reverse() override; // モーターを後退させるメソッド
  void stop() override;    // モーターを停止させるメソッド
  void setSpeed(float rate) override; // モーターの速度を設定するメソッド
};

#endif // BD62193_H