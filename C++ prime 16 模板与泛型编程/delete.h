//
// Created by 123456 on 2021/6/5.
//

#ifndef C___PRIME_16__DELETE_H
#define C___PRIME_16__DELETE_H

#include <iostream>

    /*
    template<typename T>
    class Delete
    {
        void operator()(T t) {
            std::cout << "ptr is deleting !" << std::endl;
            delete[] t;
        }
    }; */

    template<typename T>
    void Delete(T *t)
    {
        std::cout << "ptr is deleting !" << std::endl;
        delete t;
    }


#endif //C___PRIME_16__DELETE_H
