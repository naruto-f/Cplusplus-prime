//
// Created by 123456 on 2021/6/4.
//
/*  使用自定义版本sharedPoint的Blob，已调试成功，可以正常使用，和使用std::shared_ptr效果相同 */
#ifndef C___PRIME_16__BLOB2_H
#define C___PRIME_16__BLOB2_H

#include <memory>
#include <vector>
#include "Blobptr.h"
#include "sharedPointer.h"

template<typename> class Blobptr;  //前置声明，在Blob中声明友元所必须的

template<typename> class Blob2;     //运算符==中的参数所必须的

template<typename T>
bool operator==(const Blob2<T>&, const Blob2<T>&);

template<typename T>
class Blob2 {
    friend class Blobptr<T>;
    friend bool operator==<T>(const Blob2<T> &lhs, const Blob2<T> &rhs);
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    Blob2();
    Blob2(const std::initializer_list<T> &li);

    template<typename It>
    Blob2(It b, It e) : data(make_sharedPointer<std::vector<T>>(b, e)) { }

    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const T &t) { data->push_back(t); }
    void push_back(const T &&t) { data->push_back(std::move(t)); }
    void pop_back() { data->pop_back(); }
    T& front() const;
    T& back() const;
    T& operator[](size_type i);
    const T& operator[](size_type i) const;
private:
    sharedPointer<std::vector<T>> data;
    void check(size_type i, const std::string &msg) const;
};

template<typename T>
bool operator==(const Blob2<T> &lhs, const Blob2<T> &rhs) {
    return *(lhs.data) == *(rhs.data);
}

template<typename T>
inline Blob2<T>::Blob2() : data(sharedPointer<std::vector<T>>()) { }

template<typename T>
T &Blob2<T>::operator[](Blob2::size_type i) {
    check(i, "subscript out of range");
    return (*data)[i];
}

template<typename T>
void Blob2<T>::check(Blob2::size_type i, const std::string &msg) const {
    if(i >= data->size())
    {
        throw std::out_of_range(msg);
    }
}

template<typename T>
inline Blob2<T>::Blob2(const std::initializer_list<T> &li) : data(make_sharedPointer<std::vector<T>>(li)) { }

template<typename T>
T &Blob2<T>::back() const {
    check(0, "back on empty Blob !");
    return data->back();
}

template<typename T>
T &Blob2<T>::front() const {
    check(0, "front on empty Blob !");
    return data->front();
}

template<typename T>
const T &Blob2<T>::operator[](Blob2::size_type i) const {
    check(i, "subscript out of range");
    return (*data)[i];
}


#endif //C___PRIME_16__BLOB2_H
