//
// Created by 123456 on 2021/5/5.
//

#include "HasPtr.h"
/*
//大多数赋值操作组合了析构函数和拷贝构造函数的工作
HasPtr& HasPtr::operator=(const HasPtr &hp)
{
    std::string *p = new std::string(*hp.ps);
    delete ps;      //为保证自赋值操作也是正确的，应先拷贝右侧运算对象，再销毁左侧运算对象
    ps = p;
    i = hp.i;
    return *this;
}
*/
HasPtr& HasPtr::operator=(HasPtr p)
{
    swap(*this, p);   //这里使用的是自定义的swap而不是标准库中的，p是局部对象，在赋值运算符后就会自动调用HasPtr的析构函数
    return *this;
}

bool HasPtr::operator<(const HasPtr& p)
{
    return *ps < *p.ps;
}

void HasPtr::show()
{
    std::cout << "i: " << i << "   " << "string: " << *ps << std::endl;
}


inline void swap(HasPtr &h, HasPtr &p)
{
    using std::swap;
    swap(h.ps, p.ps); //这里使用的是std::swap
    swap(h.i, p.i);
    std::cout << "自定义的swap正在执行" << std::endl;
}

