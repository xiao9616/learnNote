//
// Created by 560204 on 19-6-12.
//

#ifndef OBSERVER_OBERVER_H
#define OBSERVER_OBERVER_H

#include "oberverInterFace.h"
#include <iostream>
using namespace std;
class oberver: public oberverInterFace {
public:
    void update(int number);
};


#endif //OBSERVER_OBERVER_H
