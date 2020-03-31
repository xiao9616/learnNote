#include <iostream>
using namespace std;

int add1(int a, int b) { //
    return a + b;
}

int add2(int &a, int &b) {
    return a + b;
}

int add3(int *a, int *b) {
    return *a + *b;
}

int *add4(int a, int b) {
    static int i = 1;
    int *p = &i;
    return p;
}

int &add5(int a, int b) {
    static int j = 2;
    return j;
}

int main() {
    int a = 1, b = 2;
    cout << add1(a, b) << endl;
    cout << add2(a, b) << endl;
    cout << add3(&a, &b) << endl;
    cout << *add4(a, b) << endl;
    int k;
    k = add5(a, b);
    cout << k << endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}