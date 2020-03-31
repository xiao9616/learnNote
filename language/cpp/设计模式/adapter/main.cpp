#include <iostream>
using namespace std;
class Target {
public:
    virtual void process() = 0;
};

class adaptee {
public:
    virtual void foo(int data) = 0;

    virtual int bar() = 0;
};

class adapter:public Target {
protected:
    adaptee *adaptee1;
public:
    void process() override {
        int data = adaptee1->bar();
        adaptee1->foo(data);
    }
};
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}