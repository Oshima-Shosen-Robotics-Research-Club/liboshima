#ifndef TB67H450_H
#define TB67H450_H

#include "MotorDriver.h"

class TB67H450 : public MotorDriver {
private:
  uint8_t in1, in2; // PWM 信号用のピン番号
  void run(uint8_t pwmValue1,
           uint8_t pwmValue2); // モーターを制御する内部メソッド

public:
  TB67H450(uint8_t in1, uint8_t in2); // コンストラクタ、ピン番号を初期化
  void forward() override; // モーターを前進させるメソッド
  void reverse() override; // モーターを後退させるメソッド
  void stop() override;    // モーターを停止させるメソッド
  void setSpeed(float rate) override; // モーターの速度を設定するメソッド
};

#endif // TB67H450_H