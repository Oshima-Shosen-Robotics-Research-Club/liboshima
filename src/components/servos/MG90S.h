#ifndef MG90S_H
#define MG90S_H

#include <Servo.h>

// MG90Sクラスの定義
class MG90S : public Servo {
public:
  void attach(uint8_t pin);
};

#endif // MG90S_H