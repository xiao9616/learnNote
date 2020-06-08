//
// Created by user on 2020/6/6.
//

#ifndef CHAPTER1_MESSAGE_H
#define CHAPTER1_MESSAGE_H

#pragma once

#include <iosfwd>
#include <string>
using namespace std;
class Message {
public:
    Message(const std::string &m) : message_(m) {}
    friend std::ostream &operator<<(std::ostream &os, Message &obj) {
        return obj.printObject(os);
    }
private:
    std::string message_;
    std::ostream &printObject(std::ostream &os);
};


#endif //CHAPTER1_MESSAGE_H
