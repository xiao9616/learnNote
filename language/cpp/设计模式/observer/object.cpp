//
// Created by 560204 on 19-6-12.
//

#include "object.h"

void object::notifyObserver() {
    auto it = m_oberverList.begin();

    for (; it != m_oberverList.end(); ++it) {
        (*it)->update(this->i);
    }
}

void object::setI(int i) {
    object::i = i;
}


