//
// Created by 123456 on 2021/5/9.
//

#ifndef COPY_CONTROL_STRVEC_H
#define COPY_CONTROL_STRVEC_H

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>

//简化版本(不使用模板)的vector，存储的数据类型为string
class StrVec {
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(std::initializer_list<std::string>&);
    StrVec(const StrVec&);
    StrVec& operator=(const StrVec&);
    ~StrVec();

    void push_back(const std::string&);
    size_t size() const { return first_free - elements; }
    size_t capacity() const {return cap - elements; }
    std::string *begin() { return elements; }
    std::string *end() {return first_free; }
    void reserve(size_t);
    void resize(size_t, const std::string& = "0");
    void show_all();
private:
    static std::allocator<std::string> alloc;
    void check_n_alloc()
    {
        if(size() == capacity())
            reallocate();
    }
    std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
    void free();
    void reallocate();
    std::string *elements;   //指向数组首元素的指针
    std::string *first_free;  //指向数组第一个空闲元素的指针
    std::string *cap;   //指向数组尾位置的指针
};


#endif //COPY_CONTROL_STRVEC_H
