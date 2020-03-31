//
// Created by 560204 on 19-6-14.
//

#ifndef BRIDGE_DEVICE_H
#define BRIDGE_DEVICE_H

using namespace std;

class device {
public:
    virtual void plaaSound() = 0;

    virtual void drawShape() = 0;

    virtual void writeText() = 0;

    device();

    virtual ~device();
};


#endif //BRIDGE_DEVICE_H
