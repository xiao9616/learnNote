//
// Created by 560204 on 19-6-14.
//

#include <iostream>
#include "Font.h"

Font::Font(const string &key) : key(key) {

}

void Font::printFont() {
    cout<<this->key<<endl;
}
