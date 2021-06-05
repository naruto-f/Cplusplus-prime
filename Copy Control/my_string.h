//
// Created by 123456 on 2021/5/12.
//

#ifndef COPY_CONTROL_MY_STRING_H
#define COPY_CONTROL_MY_STRING_H

#include <iostream>
#include <memory>
#include <utility>


class my_string {
    friend my_string operator+(const my_string&, const my_string&);
    friend void swap(my_string&, my_string&);
public:
    //my_string() : begin(nullptr), end(nullptr) { }
    my_string() : my_string("") { }
    explicit my_string(const char *s);
    my_string(const my_string&);
    my_string& operator=(const my_string&);
    ~my_string();

    size_t size() const { return end - begin; }
    size_t length() const { return end - begin - 1; }
    const char *c_str() const { return begin; }
    char *beg() const { return begin; }
    char *ed() const { return end; }
private:
    static std::allocator<char> alloc;
    std::pair<char*, char*> alloc_n_copy(const char* b, const char* e);
    void range_initializer(const char *beg, const char *end);
    void free();

    char *begin;  //开始的位置
    char *end;   //尾后位置
};


#endif //COPY_CONTROL_MY_STRING_H
