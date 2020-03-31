//
// Created by 560204 on 19-6-15.
//

#ifndef MEMENTO_ORIGINATOR_H
#define MEMENTO_ORIGINATOR_H

#include <string>
#include "memeto.h"

using namespace std;

class originator {
    string state;
public:
    originator(const string &state);
    memeto CreateMemeto(){
        memeto m(state);
        return m;
    }

    void setMemeto(const memeto &m){
        state = m.getState();
    }
};


#endif //MEMENTO_ORIGINATOR_H
