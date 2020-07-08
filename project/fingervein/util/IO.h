//
// Created by user on 2020/6/24.
//

#ifndef FINGERVEIN_IO_H
#define FINGERVEIN_IO_H

#ifdef linux

#include "Common.h"

#endif

using namespace std;

class IO {
public:
    virtual ~IO();
    int y = 0;

    IO();

    void getFiles(std::string path, std::vector<std::string> &files, int recursive ,int includeDir);
    void getFiles(std::string path, std::vector<std::string> &files, int recursive ,int includeDir,std::vector<int> &label);

};


#endif //FINGERVEIN_IO_H
