//------------------------------------------------------------------------------

#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

template<typename T>
class Unique_ptr
{
    T* elem;
public:
    explicit Unique_ptr(T* element) : elem{element} {}
    Unique_ptr(Unique_ptr&& a) : elem{a.elem}     // Перемещение
    { a.elem = nullptr; }

    ~Unique_ptr() { delete elem; }

    T& operator[](int n) { return elem[n]; }      // Доступ
    const T& operator[](int n) const { return elem[n]; }

    T* operator->() const { return elem; }

    T& operator*() const { return *elem; }

    T* release() { T* tmp{elem}; elem = nullptr; return tmp; }

    Unique_ptr(const Unique_ptr&) = delete;
    Unique_ptr& operator=(const Unique_ptr&) = delete;
};

//------------------------------------------------------------------------------

#endif // UNIQUE_PTR_HPP

//------------------------------------------------------------------------------
