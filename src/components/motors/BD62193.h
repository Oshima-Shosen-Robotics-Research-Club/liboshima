#ifndef BD62193_H
#define BD62193_H

#include "MotorDriver.h"

class BD62193 : public MotorDriver {
private:
  int pwmPin;
  int inAPin;
  int inBPin;
  void run(int pwmValue, bool inAState,
           bool inBState); // モーターを制御する内部メソッド

public:
  BD62193(int pwm, int inA, int inB); // コンストラクタ、ピン番号を初期化
  void forward() override; // モーターを前進させるメソッド
  void reverse() override; // モーターを後退させるメソッド
  void stop() override;    // モーターを停止させるメソッド
  void setSpeed(float rate) override; // モーターの速度を設定するメソッド
};

#endif // BD62193_H