//
// Created by 560204 on 19-6-14.
//

#include "CryptoStream.h"

CryptoStream::CryptoStream(stream *stream1) : stream1(stream1) {}

CryptoStream::~CryptoStream() {
    delete stream1;
}

void CryptoStream::read() {
    cout << "crypto stream" << endl;
    stream1->read();
}

void CryptoStream::seek() {
    cout << "crypto stream" << endl;
    stream1->seek();
}

void CryptoStream::write() {
    cout << "crypto stream" << endl;
    stream1->write();
}
