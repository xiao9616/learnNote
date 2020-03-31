//
// Created by 560204 on 19-1-24.
//

#ifndef TEST_ITERATOR_BASE_H
#define TEST_ITERATOR_BASE_H

#include <cstddef>

namespace xiao {
    struct input_iterator_tag {

    };
    struct output_iterator_tag {

    };
    struct forward_iterator_tag:public input_iterator_tag {

    };
    struct bidirectional_iterator_tag:public forward_iterator_tag{

    };
    struct random_access_iterator_tag:public bidirectional_iterator_tag {

    };

    template <typename _Category,typename _Tp,typename _Distance=ptrdiff_t, typename _Pointer=_Tp*, typename _Reference=_Tp& >
    struct iterator{
        typedef _Category iterator_category;
        typedef _Tp value_type;
        typedef _Distance difference_type;
        typedef _Pointer pointer;
        typedef _Reference reference;
    };
}
