//
// Created by 560204 on 19-6-15.
//

#ifndef MEMENTO_MEMETO_H
#define MEMENTO_MEMETO_H

#include <string>

using namespace std;
class memeto {
    string state;
public:
    memeto(const string &state);

    virtual ~memeto();

    const string &getState() const;

    void setState(const string &state);
};


#endif //MEMENTO_MEMETO_H
