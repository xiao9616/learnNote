#include <iostream>
#include "tax.h"

using namespace std;
int main() {
    TaxStrategy *taxStrategy = new CNTax;
    taxStrategy->calculate(1);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}