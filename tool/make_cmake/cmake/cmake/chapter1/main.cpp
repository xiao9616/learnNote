#include <iostream>
#include "Message.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    Message say_hello("Hello, CMake World!");
    std::cout << say_hello << std::endl;

    Message say_goodbye("Goodbye, CMake World");
    std::cout << say_goodbye << std::endl;

    return EXIT_SUCCESS;
    return 0;
}