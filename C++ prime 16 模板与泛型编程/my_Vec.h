//
// Created by 123456 on 2021/6/3.
//

#ifndef C___PRIME_16__MY_VEC_H
#define C___PRIME_16__MY_VEC_H

#include <memory>
#include <iostream>
#include <utility>

//仿照标准库容器vector
template<typename T>
class my_Vec {
public:
    my_Vec() : element(nullptr), first_free(nullptr), cap(nullptr) { }
    my_Vec(std::initializer_list<T> li);
    my_Vec(const my_Vec<T> &tem);
    my_Vec<T>& operator=(const my_Vec<T>& tem);
    ~my_Vec() { free(); }

    T& operator[](std::size_t i);
    const T& operator[](std::size_t i) const;
    std::size_t size() const { return first_free - element; }
    std::size_t capcity() const { return cap - element; }
    T* begin() const { return element; }
    T* end() const { return first_free; }
    void push_back(const T &t);
    void pop_back();
    void reverse(std::size_t newSize);
    /* 改变容器的大小，如果n比现有的size()大，则在后面每一个元素补0*/
    void resize(std::size_t n);
private:
    T* element;
    T* first_free;
    T* cap;

    static std::allocator<T> alloc;
    void reallocate();
    void check();
    std::pair<T*, T*> alloc_n_copy(const T *b, const T *e);
    //采用move移动拷贝来申请新空间，如果不能确保原先的空间一定会被释放则不要使用这种方式
    void alloc_n_move(std::size_t newSize);
    void free();
};

template<typename T>
std::allocator<T> my_Vec<T>::alloc;

template<typename T>
inline
void my_Vec<T>::check() {
    if(size() == capcity())
    {
        reallocate();
    }
}

template<typename T>
std::pair<T *, T *> my_Vec<T>::alloc_n_copy(const T *b, const T *e) {
    auto newdata = alloc.allocate(e - b);
    return {newdata, std::uninitialized_copy(b, e, newdata)};
}

template<typename T>
void my_Vec<T>::alloc_n_move(std::size_t newSize) {
    auto newdata = alloc.allocate(newSize);
    auto begin = newdata;
    auto old = element;
    std::size_t i;
    std::size_t s = size();

    for(i = 0; i < s; ++i)
    {
        alloc.construct(begin++, std::move(*old++));
    }

    free();

    element = newdata;
    first_free = begin;
    cap = element + newSize;
}

template<typename T>
void my_Vec<T>::reallocate() {
    auto newSize = element ? 2 * size() : 1;
    alloc_n_move(newSize);
}

template<typename T>
void my_Vec<T>::free() {
    if(element)
    {
        for(auto tem = first_free; tem != element; )
        {
            alloc.destroy(--tem);
        }
        alloc.deallocate(element, capcity());
    }
}

template<typename T>
my_Vec<T>::my_Vec(std::initializer_list<T> li) {
    auto newdata = alloc_n_copy(li.begin(), li.end());

    element = newdata.first;
    first_free = newdata.second;
    cap = newdata.second;
}

template<typename T>
my_Vec<T>::my_Vec(const my_Vec<T> &tem) {
    auto newdata = alloc_n_copy(tem.begin(), tem.end());

    element = newdata.first;
    first_free = newdata.second;
    cap = newdata.second;
}

template<typename T>
my_Vec<T> &my_Vec<T>::operator=(const my_Vec<T> &tem) {
    auto newdata = alloc_n_copy(tem.begin(), tem.end());  //防止自拷贝
    free();

    element = newdata.first;
    first_free = newdata.second;
    cap = newdata.second;

    return *this;
}

template<typename T>
void my_Vec<T>::push_back(const T &t) {
    check();
    alloc.construct(first_free++, t);
}

template<typename T>
void my_Vec<T>::pop_back() {
    if(size() != 0)
    {
        alloc.destroy(--first_free);
    }
}

template<typename T>
void my_Vec<T>::reverse(std::size_t newSize) {
    if(newSize > size())
    {
        alloc_n_move(newSize);
    }
}

template<typename T>
void my_Vec<T>::resize(std::size_t n) {
    if(n < size())
    {
        for(first_free; first_free != element + n; )
        {
            alloc.destroy(--first_free);
        }
    }
    else if(n > size())
    {
        for(first_free; first_free != element + n; )
        {
            check();
            alloc.construct(first_free++, T());
        }
    }
}

template<typename T>
T &my_Vec<T>::operator[](std::size_t i) {
    return *(element + i);
}

template<typename T>
const T &my_Vec<T>::operator[](std::size_t i) const {
    return *(element + i);
}


#endif //C___PRIME_16__MY_VEC_H
