//
// Created by 123456 on 2021/5/9.
//

#include "StrVec.h"

std::allocator<std::string> StrVec::alloc;

std::pair<std::string *, std::string *> StrVec::alloc_n_copy(const std::string *beg, const std::string *end)
{
    auto data = alloc.allocate(end - beg);
    return {data, std::uninitialized_copy(beg, end, data)};
}

void StrVec::push_back(const std::string &s) {
    check_n_alloc();  //每次插入之前判断是否有足够空间
    alloc.construct(first_free++, s);
}

void StrVec::free() {
    if(elements)  //使用deallocate要求elements不能为空(元素数目为0)
    {
        /*方法1：for循环
        for(auto p = first_free; p != elements; )
        {
            alloc.destroy(--p);
        }
        */
        //方法2：使用for_each和lambda表达式代替for循环destory元素：
        std::for_each(elements, first_free, [](std::string &rhs) { alloc.destroy(&rhs); });
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec::StrVec(const StrVec &str) {
    auto newdata = alloc_n_copy(str.elements, str.first_free);
    elements = newdata.first;
    first_free = newdata.second;
    cap = newdata.second;
}

StrVec::~StrVec() {
    free();
    //std::cout << "正在析构！" << std::endl;
}

StrVec& StrVec::operator=(const StrVec &str) {
    //防止自赋值问题，所以先拷贝再释放空间
    auto newdata = alloc_n_copy(str.elements, str.first_free);
    free();
    elements = newdata.first;
    first_free = newdata.second;
    cap = newdata.second;
    return *this;   //拷贝赋值运算符别忘了最后返回自身。
}

void StrVec::reallocate() {
    auto newsize = elements ? 2 * size() : 1;
    auto newelement = alloc.allocate(newsize);
    auto newpos = newelement;
    auto pos = elements;
    for(size_t i = 0; i != size(); ++i)
    {
        alloc.construct(newpos++, std::move(*pos++));  //使用标准库的移动构造函数，减少不必要的内存分配和释放，只是移交内存管理权
    }
    free();
    elements = newelement;
    first_free = newpos;
    cap = elements + newsize;
}

void StrVec::reserve(size_t n) {
    if(n > capacity())
    {
        auto newelement = alloc.allocate(n);
        auto newpos = newelement;
        auto pos = elements;
        for(size_t i = 0; i != size(); ++i)
        {
            alloc.construct(newpos++, std::move(*pos++));  //使用标准库的移动构造函数，减少不必要的内存分配和释放，只是移交内存管理权
        }
        free();
        elements = newelement;
        first_free = newpos;
        cap = elements + n;
    }
}

void StrVec::resize(size_t n, const std::string &t) {
    int num = n - size();
    if(num < 0)
    {
        num = abs(num);
        for(num; num != 0; --num)
        {
            alloc.destroy(--first_free);
        }
    }
    else if(num > 0)
    {
        while(n > capacity())
        {
            reallocate();
        }
        for(num; num != 0; --num)
        {
            alloc.construct(first_free++, t);
        }
    }
}

StrVec::StrVec(std::initializer_list<std::string> &list) {
    elements = alloc.allocate(list.size());
    first_free = elements;
    for(auto l = list.begin(); l != list.end(); ++l)
    {
        alloc.construct(first_free++, *l);
    }
    cap = first_free;
}

void StrVec::show_all() {
    auto pos = elements;
    for(int i = 0; i < size(); ++i)
    {
        std::cout << *pos++ << " ";
    }
    std::cout << std::endl;
}




