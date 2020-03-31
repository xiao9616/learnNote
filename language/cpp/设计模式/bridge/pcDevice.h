//
// Created by 560204 on 19-6-14.
//

#ifndef BRIDGE_PCDEVICE_H
#define BRIDGE_PCDEVICE_H

#include "device.h"
#include <iostream>

using namespace std;

class pcDevice :public device {
public:
    void plaaSound() override;

    void drawShape() override;

    void writeText() override;

};


#endif //BRIDGE_PCDEVICE_H
