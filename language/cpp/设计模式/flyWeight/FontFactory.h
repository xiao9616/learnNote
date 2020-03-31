//
// Created by 560204 on 19-6-14.
//

#ifndef FLYWEIGHT_FONTFACTORY_H
#define FLYWEIGHT_FONTFACTORY_H

#include <map>
#include "Font.h"

using namespace std;
class FontFactory {
private:
    map<string, Font *> fontpool;
public:
    Font *GetFont(const string &key);
};


#endif //FLYWEIGHT_FONTFACTORY_H
