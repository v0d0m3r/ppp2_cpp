//------------------------------------------------------------------------------

#ifndef VECTOR_SMALL_HPP
#define VECTOR_SMALL_HPP

//------------------------------------------------------------------------------

#include "../main_vector/Vector.hpp"

//------------------------------------------------------------------------------

template<typename T, typename A = Allocator<T>>
class Vector_small {
    Vector<T, A>* pv;
public:
    Vector_small() : pv{new Vector<T, A>{}} {}
    explicit Vector_small(int s) : pv{new Vector<T, A>(s)} {}
    Vector_small(initializer_list<T> lst) : pv{new Vector<T, A>{lst}} {}

    // Копирующие конструктор и присваивание
    Vector_small(const Vector_small& a) : pv{new Vector<T,A>{*a.pv}} {}
    Vector_small& operator=(const Vector_small& a);

    // Перемещающие конструктор и присваивание
    Vector_small(Vector_small&& a) : pv{a.pv} { a.pv = nullptr; }
    Vector_small& operator=(Vector_small&& a);

    ~Vector_small() { delete pv; }                  // Деструктор

    Vector<T, A>* operator->() const { return pv; }

    Vector<T, A>& operator*() const { return *pv; }

    T& operator[](int n) { return (*pv)[n]; }      // Доступ
    const T& operator[](int n) const { return (*pv)[n]; }

};

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector_small<T,A>& Vector_small<T,A>::operator=(const Vector_small& a)
{
    *pv = *a.pv;
    return *this;
}

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector_small<T, A>& Vector_small<T, A>::operator=(Vector_small&& a)
{
    *pv = move(*a.pv);
    return *this;                           // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

#endif // VECTOR_SMALL_HPP

//------------------------------------------------------------------------------
