/*
モータドライバは部室に複数あるのでそれぞれにクラスを作成する必要がある
このクラスが基底クラスになると思われる
*/

#ifndef MOTOR_H
#define MOTOR_H

// Motorクラスの定義
class Motor {
private:
  int pin1, pin2;                   // モーター制御用のピン番号
  void run(int input1, int input2); // モーターを制御する内部メソッド

public:
  Motor(int pin1, int pin2); // コンストラクタ、ピン番号を初期化
  void forward();            // モーターを前進させるメソッド
  void reverse();            // モーターを後退させるメソッド
  void stop();               // モーターを停止させるメソッド
};

#endif // MOTOR_H