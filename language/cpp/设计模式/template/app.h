//
// Created by 560204 on 19-6-14.
//

#ifndef TEMPLATE_APP_H
#define TEMPLATE_APP_H

#include "lib.h"

class app: public lib {
public:
    app();

    virtual ~app();

protected:
    void step2() override;

    void step4() override;

};


#endif //TEMPLATE_APP_H
