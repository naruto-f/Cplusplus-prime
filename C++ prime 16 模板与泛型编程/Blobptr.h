//
// Created by 123456 on 2021/6/2.
//

#ifndef C___PRIME_16__BLOBPTR_H
#define C___PRIME_16__BLOBPTR_H

#include <memory>
#include <vector>
#include "Blob.h"

template<typename> class Blobptr;

template<typename T>
    bool operator==(const Blobptr<T>& lhs, const Blobptr<T>& rhs);

template<typename T>
    bool operator < (const Blobptr<T>& lhs, const Blobptr<T>& rhs);

template<typename T>
class Blobptr {
    friend bool operator== <T>(const Blobptr<T>& lhs, const Blobptr<T>& rhs);
    friend bool operator< <T>(const Blobptr<T>& lhs, const Blobptr<T>& rhs);
public:
    Blobptr() : cur(0) { }
    Blobptr(const Blob<T> &b, std::size_t i = 0) : wptr(b.data), cur(i) { }

    //解引用
    T& operator*() const;

    //前置++
    Blobptr<T>& operator++();

    //前置--
    Blobptr<T>& operator--();

    //后置++
    Blobptr<T>&  operator++(int);

    //后置--
    Blobptr<T>& operator--(int);

private:
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t cur;
    std::shared_ptr<std::vector<T>> check(std::size_t i, std::string &msg) const;
};

template<typename T>
bool operator==(const Blobptr<T> &lhs, const Blobptr<T> &rhs) {
    if((lhs.wptr).lock() != (lhs.wptr).lock())  //不是同一个Blob不能比较
    {
        throw std::runtime_error("ptrs to different Blobs!");
    }
    return lhs.cur == rhs.cur;
}

template<typename T>
bool operator<(const Blobptr<T> &lhs, const Blobptr<T> &rhs) {
    if((lhs.wptr).lock() != (lhs.wptr).lock())  //不是同一个Blob不能比较
    {
        throw std::runtime_error("ptrs to different Blobs!");
    }
    return lhs.cur < rhs.cur;
}

template<typename T>
std::shared_ptr<std::vector<T>> Blobptr<T>::check(std::size_t i, std::string &msg) const {
    if(i >= (*wptr).size())
    {
        throw std::runtime_error("out of range");
    }
    return std::make_shared<std::vector<T>>(*(wptr.lock()));
}

template<typename T>
T &Blobptr<T>::operator*() const {
    auto p = check(cur, "out of range : *");
    return (*p)[cur];
}

template<typename T>
Blobptr<T> &Blobptr<T>::operator++() {
    check(cur, "increment past end of StrBlob");
    ++cur;
    return *this;
}

template<typename T>
Blobptr<T> &Blobptr<T>::operator--() {
    --cur;
    check(cur, "decrement past begin of StrBlob");
    return *this;
}

template<typename T>
Blobptr<T> &Blobptr<T>::operator--(int) {
    Blobptr<T> ret = *this;
    --(*this);
    return *this;
}

template<typename T>
Blobptr<T> &Blobptr<T>::operator++(int) {
    //不用check，会在调用前置++中检查
    Blobptr<T> ret = *this;
    ++(*this);
    return ret;
}


#endif //C___PRIME_16__BLOBPTR_H
