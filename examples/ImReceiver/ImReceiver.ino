#include <components/ImReceiver.h>

ImReceiver imReceiver(4, 5, 9600);

void setup(){
}

void loop(){
    // ImSender.inoから送信されたデータを受信する
    int data;
    if(imReceiver.receive(data)){
        Serial.println(data);
    }
}