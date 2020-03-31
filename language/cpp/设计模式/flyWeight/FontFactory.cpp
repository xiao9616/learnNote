//
// Created by 560204 on 19-6-14.
//

#include <iostream>
#include "FontFactory.h"

Font *FontFactory::GetFont(const string &key) {
    auto it = fontpool.find(key);
    if (it != fontpool.end()) {
        cout<<"already has one"<<endl;
        return fontpool[key];
    }else {
        Font *font = new Font(key);
        fontpool[key] = font;
        return font;
    }
}
