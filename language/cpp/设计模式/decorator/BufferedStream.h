//
// Created by 560204 on 19-6-14.
//

#ifndef DECORATOR_BUFFEREDSTREAM_H
#define DECORATOR_BUFFEREDSTREAM_H

#include "stream.h"
#include <iostream>

using namespace std;
class BufferedStream :public stream{
public:
    void read() override;

    void seek() override;

    void write() override;

private:
    stream* stream1;
public:
    BufferedStream(stream *stream1);

    virtual ~BufferedStream();
};


#endif //DECORATOR_BUFFEREDSTREAM_H
