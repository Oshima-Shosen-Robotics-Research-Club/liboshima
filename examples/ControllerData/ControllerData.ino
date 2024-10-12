#include <liboshima.h> // コントローラーデータ制御ライブラリをインクルード

// モーター、ボタン、スティックの数を定義
#define NUM_MOTORS 2
#define NUM_BUTTONS 2
#define NUM_STICKS 2

// ControllerDataクラスのインスタンスを作成
// NUM_MOTORS: モーターの数
// NUM_BUTTONS: ボタンの数
// NUM_STICKS: スティックの数
ControllerData<NUM_MOTORS, NUM_BUTTONS, NUM_STICKS> controllerData;

void setup() {
  // モーターの初期状態を設定
  controllerData.motors[0] = MotorStateEnum::FORWARD; // モーター1を前進に設定
  controllerData.motors[1] = MotorStateEnum::REVERSE; // モーター2を後退に設定

  // ボタンの初期状態を設定
  // ボタン1を押下状態に設定
  controllerData.buttons[0] = ButtonStateEnum::PRESSED;
  // ボタン2を解放状態に設定
  controllerData.buttons[1] = ButtonStateEnum::RELEASED;

  // スティックの初期状態を設定
  controllerData.sticks[0].x = 0;   // X軸の状態を0に設定
  controllerData.sticks[0].y = 255; // Y軸の状態を255に設定
  controllerData.sticks[1].x = 255; // X軸の状態を255に設定
  controllerData.sticks[1].y = 0;   // Y軸の状態を0に設定

  // シリアル通信の初期化
  Serial.begin(9600); // シリアル通信のボーレートを9600に設定
  Serial.println("ControllerData example"); // 初期メッセージを表示

  // モーターの状態をシリアルモニタに表示
  // "Motors: 1, 2"と表示される
  // (ArduinoIDEの場合、printfは使えないそうですが、そんなことは知りません)
  Serial.printf("Motors: %d, %d\n", controllerData.motors[0],
                controllerData.motors[1]);

  // ボタンの状態をシリアルモニタに表示
  // "Buttons: 1, 0"と表示される
  Serial.printf("Buttons: %d, %d\n", controllerData.buttons[0],
                controllerData.buttons[1]);

  // スティックの状態をシリアルモニタに表示
  // "Sticks: 0, 255, 255, 0"と表示される
  Serial.printf("Sticks: %d, %d, %d, %d\n", controllerData.sticks[0].x,
                controllerData.sticks[0].y, controllerData.sticks[1].x,
                controllerData.sticks[1].y);
}

void loop() {
  // メインループ内では特に何もしない
}