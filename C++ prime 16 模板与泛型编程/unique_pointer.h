//
// Created by 123456 on 2021/6/4.
// 说明 : 自定义版本的unique_ptr
// 注意 : shared_ptr的删除器不是类的一部分，需要额外提供; 而unique_ptr的删除器直接保存在unique_ptr模板类的对象中，第二个模板参数保存删除器的类型。
// 删除器使用演示 : ①shared_ptr : shared_ptr<int> p1(li, delete);  ②unique_ptr : unique_ptr<int, DebugDelete> p(li);
//


#ifndef C___PRIME_16__UNIQUE_POINTER_H
#define C___PRIME_16__UNIQUE_POINTER_H

#include "DebugDelete.h"

template<typename T, typename D>
class unique_pointer;

template<typename T, typename D>
void swap(unique_pointer<T, D> &lhs, unique_pointer<T, D> &rhs);

//T表示指针指向的数据的类型，D表示自定义的删除器的类型
template<typename T, typename D = DebugDelete>
class unique_pointer {
    friend void swap(unique_pointer<T, D> &lhs, unique_pointer<T, D> &rhs);
public:
    unique_pointer() = default;
    unique_pointer(const T *p) : ptr(p) { }
    /* 根据unique_ptr的性质，所以没有并拒绝拷贝构造和拷贝赋值 */
    unique_pointer(const unique_pointer &up) = delete;
    unique_pointer& operator=(const unique_pointer &up) = delete;

    /* 可以进行移动构造和移动赋值 */
    unique_pointer(unique_pointer &&up) noexcept : ptr(up.ptr) { up.ptr = nullptr; }
    unique_pointer& operator=(unique_pointer &&up) noexcept;

    /* 接受nullptr的赋值运算符，nullptr是std::nullptr_t类型的变量 */
    unique_pointer& operator=(std::nullptr_t n) noexcept;

    ~unique_pointer() { deleter(ptr); ptr = nullptr; }

    //运算符重载
    operator bool() const { return ptr ? true : false; }
    T& operator*() const {return *ptr; }
    T* operator->() const { return &this->operator*(); } //显式调用了*运算符

    //获取底层指针
    T* get() const { return ptr; }

    //重置unique_ptr
    void reset() noexcept
    {
        deleter(ptr);
        ptr = nullptr;
    }

    void reset(T* p) noexcept
    {
        deleter(ptr);
        ptr = p;
    }

    //交换两个unique_ptr
    void swap(unique_pointer &up)
    {
        ::swap(*this, up);
    }

    //释放当前unique_ptr保存的指针，并返回这个指针
    T* release()
    {
        auto ret = ptr;
        deleter(ptr);
        ptr = nullptr;
        return ret;
    }

private:
    T *ptr = nullptr;
    D deleter = D();
};

template<typename T, typename D>
inline void swap(unique_pointer<T, D> &lhs, unique_pointer<T, D> &rhs) {
    using std::swap;
    swap(lhs.ptr, rhs.ptr);
    swap(lhs.deleter, rhs.deleter);
}


template<typename T, typename D>
inline unique_pointer<T, D> &unique_pointer<T, D>::operator=(unique_pointer &&up) noexcept {
    if(this->ptr != up.ptr)
    {
        deleter(ptr);
        ptr = nullptr;
        ::swap(*this, up);
    }
    return *this;
}

template<typename T, typename D>
unique_pointer<T, D> &unique_pointer<T, D>::operator=(std::nullptr_t n) noexcept {
    if(n == nullptr)
    {
        deleter(ptr);
        ptr = nullptr;
    }
    return *this;
}

#endif //C___PRIME_16__UNIQUE_POINTER_H
