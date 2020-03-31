//
// Created by 560204 on 19-6-12.
//

#ifndef OBSERVER_OBJECTINTERFACE_H
#define OBSERVER_OBJECTINTERFACE_H

#include <iostream>
#include <list>
#include "oberverInterFace.h"
using namespace std;
class objectInterface {
protected:
    list<oberverInterFace *> m_oberverList;

public:
    void add(oberverInterFace* obj);

    void remove(oberverInterFace* obj);

    virtual void notifyObserver();
};



#endif //OBSERVER_OBJECTINTERFACE_H
