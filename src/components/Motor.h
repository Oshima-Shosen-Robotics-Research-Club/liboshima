#ifndef MOTOR_H
#define MOTOR_H

class Motor {
private:
  int pin1, pin2;                   // モーター制御用のピン
  void Run(int input1, int input2); // モーターを制御する内部メソッド

public:
  Motor(int pin1, int pin2); // コンストラクタ
  void Forward();            // 正転メソッド
  void Reverse();            // 後転メソッド
  void Stop();               // モーター停止メソッド
};

#endif
