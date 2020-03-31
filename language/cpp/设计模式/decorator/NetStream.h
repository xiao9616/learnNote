//
// Created by 560204 on 19-6-14.
//

#ifndef DECORATOR_NETSTREAM_H
#define DECORATOR_NETSTREAM_H

#include "stream.h"
#include <iostream>

using namespace std;

class NetStream :public stream {
public:
    virtual void read() override;

    virtual void seek() override;

    virtual void write() override;

};


#endif //DECORATOR_NETSTREAM_H
