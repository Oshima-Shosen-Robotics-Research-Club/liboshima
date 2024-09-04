#include <components/ims/ImSender.h>

ImSender imSender(2, 3);

void setup(){
    // 送信データを送信する
    int data = 123;
    imSender.send(data);
}

void loop(){
}