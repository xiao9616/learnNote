//
// Created by 560204 on 19-6-15.
//

#include "memeto.h"

memeto::memeto(const string &state) : state(state) {}

memeto::~memeto() {

}

const string &memeto::getState() const {
    return state;
}

void memeto::setState(const string &state) {
    memeto::state = state;
}
