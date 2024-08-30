#include <components/Motor.h>

Motor motor(2, 3);

void setup(){
}

void loop(){
    // モーターを前進させる
    motor.forward();
    delay(1000);
    // モーターを停止させる
    motor.stop();
    delay(1000);
    // モーターを後退させる
    motor.reverse();
    delay(1000);
    // モーターを停止させる
    motor.stop();
    delay(1000);
}