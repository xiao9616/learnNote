//
// Created by 560204 on 19-6-12.
//

#ifndef OBSERVER_OBJECT_H
#define OBSERVER_OBJECT_H

#include <list>
#include <iostream>
#include "objectInterface.h"
#include "oberverInterFace.h"
using namespace std;

class object : public objectInterface {
    int i;
public:
    void setI(int i);

    void notifyObserver();
};


#endif //OBSERVER_OBJECT_H
