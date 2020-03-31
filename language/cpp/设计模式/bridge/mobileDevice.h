//
// Created by 560204 on 19-6-14.
//

#ifndef BRIDGE_MOBILEDEVICE_H
#define BRIDGE_MOBILEDEVICE_H

#include <iostream>
#include "device.h"
using namespace std;

class mobileDevice: public device {
public:
    void plaaSound() override;

    void drawShape() override;

    void writeText() override;

};


#endif //BRIDGE_MOBILEDEVICE_H
