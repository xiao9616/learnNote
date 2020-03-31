//
// Created by 560204 on 19-6-14.
//

#ifndef STRATEGY_TAX_H
#define STRATEGY_TAX_H
#include "TaxStrategy.h"
#include <iostream>
using namespace std;

class CNTax:public TaxStrategy {
public:
    double calculate(int number) override {
        cout << "CNTax" << endl;
    }
};

class USTax:public TaxStrategy {
public:
    double calculate(int number) override {
        cout << "USTax" << endl;
    }
};
#endif //STRATEGY_TAX_H
