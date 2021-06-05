//
// Created by 123456 on 2021/6/2.
//

#ifndef C___PRIME_16__BLOB_H
#define C___PRIME_16__BLOB_H

#include <memory>
#include <vector>

template<typename> class Blobptr;  //前置声明，在Blob中声明友元所必须的

template<typename> class Blob;     //运算符==中的参数所必须的

template<typename T>
    bool operator==(const Blob<T>&, const Blob<T>&);


template<typename T>
class Blob {
    friend class Blobptr<T>;
    friend bool operator==<T>(const Blob<T> &lhs, const Blob<T> &rhs);
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    Blob();
    Blob(const std::initializer_list<T> li);

    template<typename It>
    Blob(It b, It e) : data(std::make_shared<std::vector<T>>(b, e)) { }

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
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i, const std::string &msg) const;
};

template<typename T>
bool operator==(const Blob<T> &lhs, const Blob<T> &rhs) {
    return *(lhs.data) == *(rhs.data);
}

template<typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) { }

template<typename T>
T &Blob<T>::operator[](Blob::size_type i) {
    check(i, "subscript out of range");
    return (*data)[i];
}

template<typename T>
void Blob<T>::check(Blob::size_type i, const std::string &msg) const {
    if(i >= data->size())
    {
        throw std::out_of_range(msg);
    }
}

template<typename T>
Blob<T>::Blob(const std::initializer_list<T> li) : data(std::make_shared<std::vector<T>>(li)) { }

template<typename T>
T &Blob<T>::back() const {
    check(0, "back on empty Blob !");
    return data->back();
}

template<typename T>
T &Blob<T>::front() const {
    check(0, "front on empty Blob !");
    return data->front();
}

template<typename T>
const T &Blob<T>::operator[](Blob::size_type i) const {
    check(i, "subscript out of range");
    return (*data)[i];
}


#endif //C___PRIME_16__BLOB_H
