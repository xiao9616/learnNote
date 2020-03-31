//
// Created by 560204 on 19-6-14.
//

#ifndef BRIDGE_MEAAGEPERFECT_H
#define BRIDGE_MEAAGEPERFECT_H

#include <iostream>
#include "message.h"

using namespace std;

class meaagePerfect :public message {
public:
    meaagePerfect(device *device1);

private:
    void Login() override;

    void sendMessage() override;

    void sendPicture() override;

};


#endif //BRIDGE_MEAAGEPERFECT_H
