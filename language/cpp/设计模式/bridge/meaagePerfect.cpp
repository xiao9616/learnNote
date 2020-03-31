//
// Created by 560204 on 19-6-14.
//

#include "meaagePerfect.h"

void meaagePerfect::Login() {
    device1->plaaSound();
    device1->plaaSound();
}

void meaagePerfect::sendMessage() {
    device1->plaaSound();
    device1->writeText();
}

void meaagePerfect::sendPicture() {
    device1->plaaSound();
    device1->drawShape();
}

meaagePerfect::meaagePerfect(device *device1){
    this->device1 = device1;
}
