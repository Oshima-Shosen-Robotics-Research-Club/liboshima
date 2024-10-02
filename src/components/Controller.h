#pragma once

#include <stddef.h>

#pragma pack(push, 1)
// テンプレートクラスとしてControllerを定義
template <size_t numBtns = 8, size_t numSticks = 8> struct Controller {
  // デジタルボタンの状態を保持する配列
  struct DigitalButton {
    uint8_t pin1 : 1;
    uint8_t pin2 : 1;
  } digitalBtns[numBtns];

  // アナログスティックの状態を保持する配列
  struct AnalogStick {
    uint8_t x;
    uint8_t y;
  } analogSticks[numSticks];
};
#pragma pack(pop)
