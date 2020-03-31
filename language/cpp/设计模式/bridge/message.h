//
// Created by 560204 on 19-6-14.
//

#ifndef BRIDGE_MESSAGE_H
#define BRIDGE_MESSAGE_H


#include "device.h"

class message {
protected:
    device* device1;
public:


    virtual void Login() = 0;

    virtual void sendMessage() = 0;

    virtual void sendPicture() = 0;
};



#endif //BRIDGE_MESSAGE_H
