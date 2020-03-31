//
// Created by 560204 on 19-6-12.
//

#include "objectInterface.h"


void objectInterface::add(oberverInterFace *obj) {
    m_oberverList.push_back(obj);

}

void objectInterface::remove(oberverInterFace *obj) {
    m_oberverList.remove(obj);
}

void objectInterface::notifyObserver() {

}

