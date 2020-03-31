#include <iostream>
#include "object.h"
#include "oberver.h"

using namespace std;
int main() {
    oberver *oberver1 = new oberver();
    oberver *oberver2 = new oberver();
    oberver *oberver3 = new oberver();
    object *object1 = new object();
    object1->add(oberver1);
    object1->add(oberver2);
    object1->add(oberver3);
    object1->setI(12);
    object1->notifyObserver();
    object1->setI(100);
    object1->notifyObserver();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}