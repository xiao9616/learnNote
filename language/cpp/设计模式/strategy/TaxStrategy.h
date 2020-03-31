//
// Created by 560204 on 19-6-14.
//

#ifndef STRATEGY_TAXSTRATEGY_H
#define STRATEGY_TAXSTRATEGY_H


class TaxStrategy {
public:
    TaxStrategy();

    virtual double calculate(int number) = 0;

    virtual ~TaxStrategy();
};


#endif //STRATEGY_TAXSTRATEGY_H
