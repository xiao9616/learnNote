#include <iostream>
using namespace std;

template<typename T>
class iterator {
public:
    virtual void first() = 0;

    virtual void next() = 0;

    virtual bool isDone() = 0;

    virtual T &current() = 0;
};

template <typename T>
class Mycollection{
public:
    iterator<T> getIterator(){
        return new iterator<T>();
    }
};

template <typename T>
class CollectionIterator:public iterator<T>{
    Mycollection<T> mc;
public:
    void first() override {

    }

    void next() override {

    }

    bool isDone() override {
        return false;
    }

    T &current() override {
        return <#initializer#>;
    }
};
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}