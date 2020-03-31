//
// Created by 560204 on 19-1-25.
//

#ifndef TEST_VARADICTEMPLATE_H
#define TEST_VARADICTEMPLATE_H

#include <iostream>
#include <vector>

using namespace std;

template<typename _Tp>
inline _Tp
max(initializer_list<_Tp> _l) {
    return *max_element(_l.begin(), _l.end());
}

int maximum(int n)
{
    return n;
}

template<typename... args>
int maximum(int n,args... arg)
{
    return std::max(n,maximum(arg...));
}
#endif //TEST_VARADICTEMPLATE_H
