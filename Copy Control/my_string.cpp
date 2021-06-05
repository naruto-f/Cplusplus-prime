//
// Created by 123456 on 2021/5/12.
//

#include "my_string.h"

std::allocator<char> my_string::alloc;
my_string::my_string(const my_string &s)
{
    range_initializer(s.begin, s.end);
}

std::pair<char *, char *> my_string::alloc_n_copy(const char *b, const char *e) {
    auto newdata = alloc.allocate(e - b);
    return {newdata, std::uninitialized_copy(b, e, newdata)};
}

void my_string::free() {
    auto pos = end;
    for(end; pos != begin; )
    {
        alloc.destroy(--pos);
    }
    alloc.deallocate(begin, end - begin);
}

my_string::~my_string() {
    free();
}

my_string &my_string::operator=(const my_string &s) {
    auto newdata = alloc_n_copy(s.begin, s.end);
    free();
    begin = newdata.first;
    end = newdata.second;
    return *this;
}

my_string operator+(const my_string &s1, const my_string &s2) {

}

void my_string::range_initializer(const char *beg, const char *end) {
    auto newdata = alloc_n_copy(beg, end);
    begin = newdata.first;
    end = newdata.second;
}

my_string::my_string(const char *s)
{
    char *ss = const_cast<char*>(s);
    while(*ss)
    {
        ++ss;
    }
    range_initializer(s, ++ss);
}






