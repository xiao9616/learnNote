//
// Created by 560204 on 19-6-14.
//

#include "messageLite.h"

void messageLite::Login() {
    device1->plaaSound();
}

void messageLite::sendMessage() {
    device1->writeText();
}

void messageLite::sendPicture() {
    device1->drawShape();
}
messageLite::messageLite(device *device1){
    this->device1 = device1;
}