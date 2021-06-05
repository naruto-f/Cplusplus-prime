//
// Created by 123456 on 2021/5/7.
//

#ifndef COPY_CONTROL_HASPTR2_H
#define COPY_CONTROL_HASPTR2_H

#include <iostream>

//类指针版本的HasPtr
class HasPtr2 {
public:
    HasPtr2(const std::string s = std::string()) : ps(new std::string(s)), i(0), use(new std::size_t(1)) { }
    HasPtr2(const HasPtr2 &p) : ps(new std::string(*p.ps)), i(p.i), use(p.use) { ++*use; }
    HasPtr2& operator=(const HasPtr2&);
    ~HasPtr2();
private:
    std::string *ps;
    int i;
    std::size_t *use;  //使用动态内存的引用计数器的指针
};


#endif //COPY_CONTROL_HASPTR2_H
