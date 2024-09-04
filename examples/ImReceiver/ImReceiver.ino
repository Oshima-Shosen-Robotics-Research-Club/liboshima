#include <components/ims/ImReceiver.h>

ImReceiver imReceiver(4, 5);

void setup(){
}

void loop(){
    // ImSender.inoから送信されたデータを受信する
    int data;
    if(imReceiver.receive(data)){
        Serial.println(data);
    }
}