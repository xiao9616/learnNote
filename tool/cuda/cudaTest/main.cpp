#include <iostream>
extern "C" {
    void useCUDA();
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    useCUDA();
    return 0;
}