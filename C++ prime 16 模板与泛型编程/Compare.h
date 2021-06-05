//
// Created by 123456 on 2021/6/2.
//

#ifndef C___PRIME_16__COMPARE_H
#define C___PRIME_16__COMPARE_H

#include <cstring>

//数据类型作为模板参数
/* 此版本不能用于指针的比较
template <typename T>
int single_compare(const T &l, const T &r)
{
    if(l < r)
    {
        return -1;
    }
    if(r < l)
    {
        return 1;
    }
    return 0;
}
*/

template <typename T>
int single_compare(const T &l, const T &r)
{
    if(std::less<T>()(l, r))
    {
        return -1;
    }
    if(std::less<T>()(r, l))
    {
        return 1;
    }
    return 0;
}


//非数据类型作为模板参数
template <unsigned N, unsigned M>
int array_compare(const char (&p1)[N], const char (&p2)[M])
{
    return strcmp(p1, p2);
}





#endif //C___PRIME_16__COMPARE_H
