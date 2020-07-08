//
// Created by user on 2020/7/3.
//

#ifndef FINGERVEIN_TESTINTERFACE_H
#define FINGERVEIN_TESTINTERFACE_H

#include "../util/Common.h"
#include "../util/IO.h"

class testInterface {
protected:
    vector<int> y1;
    vector<int> y2;
    vector<string> dataBase;
    vector<string> input;
public:

    virtual void setDataBase(const String &path) {
        IO *io = new IO();
        io->getFiles(path, this->dataBase, 1, 0, y1);
        delete io;
    }

    virtual void setInput(const String &inputPath) {
        IO *io = new IO();
        io->getFiles(inputPath, this->input, 1, 0, y2);
        delete io;
    }

    virtual float getPassPrecent() = 0;

    virtual void run() = 0;

public:
    testInterface() {}

    virtual ~testInterface() {

    }
};


#endif //FINGERVEIN_TESTINTERFACE_H
