//
// Created by 560204 on 19-6-14.
//

#ifndef FLYWEIGHT_FONT_H
#define FLYWEIGHT_FONT_H

#include <string>
using namespace std;
class Font {
private:
    string key;
public:
    Font(const string &key);

    void printFont();

};


#endif //FLYWEIGHT_FONT_H
