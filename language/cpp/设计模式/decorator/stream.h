//
// Created by 560204 on 19-6-14.
//

#ifndef DECORATOR_STREAM_H
#define DECORATOR_STREAM_H


#include <zconf.h>

class stream {
public:
    stream();

    virtual void read()=0;
    virtual void seek()=0;
    virtual void write()=0;

    virtual ~stream();
};


#endif //DECORATOR_STREAM_H
