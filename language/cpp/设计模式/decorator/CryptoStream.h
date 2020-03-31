//
// Created by 560204 on 19-6-14.
//

#ifndef DECORATOR_CRYPTOSTREAM_H
#define DECORATOR_CRYPTOSTREAM_H

#include "stream.h"
#include <iostream>
using namespace std;
class CryptoStream :public stream{
    stream* stream1;
public:
    CryptoStream(stream *stream1);

    virtual ~CryptoStream();

    void read() override;

    void seek() override;

    void write() override;
};


#endif //DECORATOR_CRYPTOSTREAM_H
