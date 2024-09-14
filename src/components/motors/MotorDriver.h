#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>

class MotorDriver {
public:
  // モーターの速度を設定するメソッド
  virtual void setSpeed(float rate) = 0;

  // モーターを前進させるメソッド
  virtual void forward() = 0;

  // モーターを後退させるメソッド
  virtual void reverse() = 0;

  // モーターを停止させるメソッド
  virtual void stop() = 0;
};

#endif // MOTOR_DRIVER_H