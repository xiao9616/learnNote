//
// Created by 560204 on 19-6-14.
//

#include "BufferedStream.h"

BufferedStream::BufferedStream(stream *stream1) : stream1(stream1) {}

BufferedStream::~BufferedStream() {

}

void BufferedStream::read() {
    cout << "buffer stream" << endl;
    stream1->read();
}

void BufferedStream::seek() {
    cout << "buffer stream" << endl;
    stream1->seek();
}

void BufferedStream::write() {
    cout << "buffer stream" << endl;
    stream1->write();
}
