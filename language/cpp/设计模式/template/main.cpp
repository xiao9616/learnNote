#include <iostream>
#include "app.h"
using namespace std;

int main() {
    lib *pLib = new app();
    pLib->run();
    delete pLib;
    return 0;
}