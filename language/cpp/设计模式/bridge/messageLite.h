//
// Created by 560204 on 19-6-14.
//

#ifndef BRIDGE_MESSAGELITE_H
#define BRIDGE_MESSAGELITE_H

#include "message.h"
using namespace std;

class messageLite:public message {
public:
    messageLite(device *device1);

private:
    void Login() override;

    void sendMessage() override;

    void sendPicture() override;

};




#endif //BRIDGE_MESSAGELITE_H
