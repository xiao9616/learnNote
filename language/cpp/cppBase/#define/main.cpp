#include <iostream>
using namespace std;
#define debug 0
#define concat(a, b) a ## b
int main() {

#ifndef debug
    std::cout << "Hello, World!" << std::endl;
#endif

    int xy = 100;

    cout << concat(x, y);

    cout << "Value of __LINE__ : " << __LINE__ << endl;
    cout << "Value of __FILE__ : " << __FILE__ << endl;
    cout << "Value of __DATE__ : " << __DATE__ << endl;
    cout << "Value of __TIME__ : " << __TIME__ << endl;

    return 0;
}