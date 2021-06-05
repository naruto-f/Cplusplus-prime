//
// Created by 123456 on 2021/6/4.
//

#ifndef C___PRIME_16__DEBUGDELETE_H
#define C___PRIME_16__DEBUGDELETE_H

#include <iostream>

class DebugDelete {
public:
    DebugDelete(std::ostream &o = std::cerr) : os(o) { }
    template <typename T>
    void operator()(T *p) const
    {
        std::cout << "delete unique ptr !" << std::endl;
        delete p;
    }

private:
    std::ostream &os;
};


#endif //C___PRIME_16__DEBUGDELETE_H
