//
// Created by 560204 on 19-6-14.
//

#ifndef DECORATOR_FILESTREAM_H
#define DECORATOR_FILESTREAM_H

#include <iostream>
#include "stream.h"
using namespace std;

class FileStream :public stream {
public:
    virtual void read() override;

    virtual void seek() override;

    virtual void write() override;

};


#endif //DECORATOR_FILESTREAM_H
