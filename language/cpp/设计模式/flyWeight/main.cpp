#include <iostream>
#include "Font.h"
#include "FontFactory.h"

using namespace std;
int main() {
    FontFactory *fontFactory = new FontFactory();
    Font *font = fontFactory->GetFont("123");
    font->printFont();
    Font *font1 = fontFactory->GetFont("123");
    font1->printFont();
    return 0;
}