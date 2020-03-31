//
// Created by 560204 on 19-6-14.
//

#ifndef TEMPLATE_LIB_H
#define TEMPLATE_LIB_H

#include <iostream>

using namespace std;

class lib {
public:
    lib();

public:
    void run();

    virtual ~lib();

protected:
    void step1();
    void step3();
    void step5();

    virtual void step2() = 0;

    virtual void step4() = 0;
};


#endif //TEMPLATE_LIB_H
