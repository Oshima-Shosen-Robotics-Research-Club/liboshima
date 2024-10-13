#include <liboshima.h> // コントローラーデータ制御ライブラリをインクルード

// モーター、ボタン、スティックの数を定義
#define NUM_MOTOR_BUTTONS 2
#define NUM_OTHER_BUTTONS 2
#define NUM_STICKS 2

// ControllerDataクラスのインスタンスを作成
// NUM_MOTOR_BUTTONS: モーターの数
// NUM_OTHER_BUTTONS: ボタンの数
// NUM_STICKS: スティックの数
ControllerData<NUM_MOTOR_BUTTONS, NUM_OTHER_BUTTONS, NUM_STICKS> controllerData;

void setup() {
  // モーターの初期状態を設定
  // モーター1を前進に設定
  controllerData.motorButtons[0] = MotorButtonStateEnum::FORWARD;
  // モーター2を後退に設定
  controllerData.motorButtons[1] = MotorButtonStateEnum::REVERSE;

  // ボタンの初期状態を設定
  // ボタン1を押下状態に設定
  controllerData.otherButtons[0] = AnotherButtonStateEnum::PRESSED;
  // ボタン2を解放状態に設定
  controllerData.otherButtons[1] = AnotherButtonStateEnum::RELEASED;

  // スティックの初期状態を設定
  controllerData.sticks[0].x = 0;   // X軸の状態を0に設定
  controllerData.sticks[0].y = 255; // Y軸の状態を255に設定
  controllerData.sticks[1].x = 255; // X軸の状態を255に設定
  controllerData.sticks[1].y = 0;   // Y軸の状態を0に設定

  // シリアル通信の初期化
  Serial.begin(9600); // シリアル通信のボーレートを9600に設定
  Serial.println("ControllerData example"); // 初期メッセージを表示

  char buf[64]; // メッセージを格納するバッファ

  // モーターの状態をシリアルモニタに表示
  // "Motors: 1, 2"と表示される
  sprintf(buf, "Motors: %d, %d", controllerData.motorButtons[0],
          controllerData.motorButtons[1]);
  Serial.print(buf);

  // ボタンの状態をシリアルモニタに表示
  // "Buttons: 1, 0"と表示される
  sprintf(buf, "Buttons: %d, %d", controllerData.otherButtons[0],
          controllerData.otherButtons[1]);
  Serial.print(buf);

  // スティックの状態をシリアルモニタに表示
  // "Stick 1: X=0, Y=255"と表示される
  sprintf(buf, "Stick 1: X=%d, Y=%d", controllerData.sticks[0].x,
          controllerData.sticks[0].y);
  Serial.print(buf);
}

void loop() {
  // メインループ内では特に何もしない
}