#include <iostream>
#include "stream.h"
#include "CryptoStream.h"
#include "FileStream.h"
#include "NetStream.h"
#include "BufferedStream.h"

using namespace std;
int main() {
    stream *stream1 = new FileStream();
    stream *stream2 = new CryptoStream(stream1);
    stream2->read();
    stream2->seek();
    stream2->write();
    cout << "====================" << endl;
    stream *stream3 = new BufferedStream(stream1);
    stream3->read();
    stream3->seek();
    stream3->write();
    cout << "====================" << endl;
    stream *stream4 = new BufferedStream(stream2);
    stream4->read();
    stream4->seek();
    stream4->write();

    return 0;
}