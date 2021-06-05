//
// Created by 123456 on 2021/6/4.
// 说明 : 自定义版本的shared_ptr
//

#ifndef C___PRIME_16__SHAREDPOINTER_H
#define C___PRIME_16__SHAREDPOINTER_H

#include <iostream>
#include <memory>
#include <functional>
#include "delete.h"

template<typename>
class sharedPointer;

template<typename T>
void swap(sharedPointer<T> &lhs, sharedPointer<T> &rhs);

template<typename T, typename It>
sharedPointer<T> make_sharedPointer(It b, It e);

template<typename T>
sharedPointer<T> make_sharedPointer(T &t);

template<typename T>
class sharedPointer {
    friend void swap<T>(sharedPointer<T> &lhs, sharedPointer<T> &rhs);
    template<typename, typename It>
    friend sharedPointer<T> make_sharedPointer(It b, It e);
    friend sharedPointer<T> make_sharedPointer(T &t);
public:
    sharedPointer() : ptr(new T()), refcount(new std::size_t(1)), deleter(Delete<T>) {}

    sharedPointer(T *t) : ptr(t), refcount(new std::size_t(1)), deleter(Delete<T>) {}

    sharedPointer(const sharedPointer<T> &sp) : ptr(sp.ptr), refcount(sp.refcount), deleter(sp.deleter) {
        ++(*refcount);
    }

    sharedPointer(sharedPointer<T> &&sp) noexcept: ptr(sp.ptr), refcount(sp.refcount),
                                                   deleter(std::move(sp.deleter)) {
        sp.ptr = nullptr;
        sp.refcount = nullptr;
    }

    sharedPointer<T> &operator=(const sharedPointer<T> &sp);

    sharedPointer<T> &operator=(sharedPointer<T> &&sp) noexcept;

    ~sharedPointer() { decrement_and_destroy(); }

    operator bool() const { return ptr ? true : false; }

    T *operator->() const { return &(*ptr); }

    T &operator*() { return *ptr; }

    const T &operator*() const { return *ptr; }

    std::size_t use_count() const { return *refcount; }

    T *get() const { return ptr; }

    bool unique() { return 1 == *refcount; }

    void m_swap(sharedPointer &sp);

    void reset() {
        decrement_and_destroy();
    }

    void reset(T *pointer) {
        if (ptr != pointer) {
            decrement_and_destroy();
            ptr = pointer;
            refcount = new std::size_t(1);
        }
    }

    void reset(T *pointer, const std::function<void(T *)> &d) {
        reset(pointer);
        deleter = d;
    }
private:
    T *ptr;
    std::size_t *refcount;
    std::function<void(T *)> deleter;

    void decrement_and_destroy() {
        if (ptr && 0 == --*refcount) {
            delete refcount;
            deleter(ptr);
        } else if (!ptr) {
            delete refcount;
        }
        ptr = nullptr;
        refcount = nullptr;
    }
};

template<typename T>
sharedPointer<T> &sharedPointer<T>::operator=(const sharedPointer<T> &sp) {
    ++(*sp.refcount);
    decrement_and_destroy();
    ptr = sp.ptr;
    refcount = sp.refcount;
    deleter = sp.deleter;
    return *this;
}

template<typename T>
sharedPointer<T> &sharedPointer<T>::operator=(sharedPointer<T> &&sp) noexcept {
    m_swap(sp);
    sp.decrement_and_destroy();
    return *this;
}

template<typename T>
void sharedPointer<T>::m_swap(sharedPointer &sp) {
    if (sp != *this) {
        ::swap(*this, sp);
    }
}

template<typename T>
void swap(sharedPointer<T> &lhs, sharedPointer<T> &rhs)
{
    using std::swap;
    swap(lhs.ptr, rhs.ptr);
    swap(lhs.refcount, rhs.refcount);
    swap(lhs.deleter, rhs.deleter);
}

template<typename T, typename It>
sharedPointer<T> make_sharedPointer(It b, It e)
{
    T *res = new T(b, e);
    return sharedPointer<T>(res);
}

template<typename T>
sharedPointer<T> make_sharedPointer(const T &t)
{
    T *res = new T(t.begin(), t.end());
    return sharedPointer<T>(res);
}

#endif //C___PRIME_16__SHAREDPOINTER_H
