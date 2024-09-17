#ifndef HS_485HB_H
#define HS_485HB_H

#include <Servo.h>

// HS_485HBクラスの定義
class HS_485HB : public Servo {
public:
  void attach(uint8_t pin);
};

#endif // HS_485HB_H