//
// Created by 123456 on 2021/5/7.
//

#include "HasPtr2.h"


HasPtr2& HasPtr2::operator=(const HasPtr2 &rhs)
{
    ++(*rhs.use);   //先递增右侧运算对象的引用计数，可以解决自赋值问题
    if(--*use == 0)
    {
        delete ps;
        ps = nullptr;
        delete use;
        use = nullptr;
    }
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;
}


HasPtr2::~HasPtr2()
{
    if(--*use == 0)
    {
        delete ps;
        ps = nullptr;
        delete use;
        use = nullptr;
    }
}
