//
// Created by 123456 on 2021/6/2.
//

#ifndef C___PRIME_16__MY_FIND_H
#define C___PRIME_16__MY_FIND_H

#include <iostream>

//函数模板：搜索标准库容器中是否存在指定元素
template <typename iter, typename T>
bool find(const iter &begin, const iter &end, T target)
{
    iter b = begin;
    for(b = begin; b != end; ++b)
    {
        if(*b == target)
        {
            return true;
        }
    }
    return false;
}

//函数模板：能打印任意大小，任意数据类型的数组
template<typename T, unsigned N>
void print(T (&arr)[N])  /* 接收一个任意数组的引用 */
{
    unsigned i = 0;
    for(i = 0; i != N; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

//类似于标准库的begin
template<typename T, unsigned N>
T* my_begin(T (&arr)[N])
{
    return arr;
}

//类似于标准库的end,返回尾后位置
//注意：不能对my_end的返回值解引用和使用++操作
template<typename T, unsigned N>
T* my_end(T (&arr)[N])
{
    return arr + N;
}

//一个constexpr模板：返回给定数组的大小
template<typename T, unsigned N> constexpr
unsigned size(T (&arr)[N])
{
    return N;
}

/* 接受一个容器的引用，使用容器的size_type和size成员来打印容器中的元素 */
template<typename Container>
void print_Con1(const Container &c)
{
    typename Container::size_type i = 0;
    for(i = 0; i < c.size(); ++i)
    {
        std::cout << c[i] << " ";
    }
    std::cout << std::endl;
}

/* 接受一个容器的引用，使用容器的迭代器成员begin和end来打印容器中的元素 */
template<typename Container>
void print_Con2(const Container &c)
{
    for(auto be = c.begin(); be != c.end(); ++be)
    {
        std::cout << *be << " ";
    }
    std::cout << std::endl;
}


#endif //C___PRIME_16__MY_FIND_H
