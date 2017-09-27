//------------------------------------------------------------------------------

#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

template<typename T>
struct Allocator
{
    T* allocate(size_t n)
    {
        T* p{static_cast<T*>(malloc(sizeof(T) * n))};
        if (p) return p;
        throw bad_alloc();
    }
    void deallocate(T* p, size_t) { free(p); }

    void construct(T* p, const T& v) { new (p) T(v); }
    void destroy(T* p) { p->~T(); }
};

//------------------------------------------------------------------------------

#endif // ALLOCATOR_HPP

//------------------------------------------------------------------------------
