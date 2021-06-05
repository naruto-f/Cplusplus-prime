//
// Created by 123456 on 2021/5/5.
//

#ifndef COPY_CONTROL_HASPTR_H
#define COPY_CONTROL_HASPTR_H

#include <iostream>

//类值版本的HasPtr
class HasPtr {
    friend void swap(HasPtr&, HasPtr&);
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) { }
   /* //赋值运算符版本1：常规版本
    HasPtr &operator=(const HasPtr &); */
    //赋值运算符版本2：使用自定义的交换swap和拷贝(参数值传递)，自动处理自赋值情况且天然就是异常安全的
    HasPtr& operator=(HasPtr);
    bool operator<(const HasPtr&);
    ~HasPtr() { delete ps; }

    void show();

private:
    int i;
    std::string *ps;

private:
};


#endif //COPY_CONTROL_HASPTR_H
