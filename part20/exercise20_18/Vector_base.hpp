//------------------------------------------------------------------------------

#ifndef VECTOR_BASE_HPP
#define VECTOR_BASE_HPP

//------------------------------------------------------------------------------

#include "Allocator.hpp"

//------------------------------------------------------------------------------

template<typename T, typename A>
struct Vector_base {
    A alloc;    // Распределитель памяти
    T* elem;    // Начало выделенной памяти
    int sz;     // Количество элементов
    int space;  // Размер выделенной памяти

    Vector_base() : alloc{A{}}, elem{nullptr}, sz{0}, space{0} {}
    Vector_base(const A& a, int size, int n = 0);

    // Копирующие конструктор и присваивание
    Vector_base(const Vector_base &a) : Vector_base{a.alloc, a.sz} {}
    Vector_base& operator=(const Vector_base& a);

    // Перемещающие конструктор и присваивание
    Vector_base(Vector_base&& a);
    Vector_base& operator=(Vector_base&& a);

    ~Vector_base() { alloc.deallocate(elem, space); }
};

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector_base<T, A>::Vector_base(const A& a, int size, int n)
    : alloc{a},
      elem{alloc.allocate(n ? n : size)},
      sz{size}, space(n ? n : size)
{

}

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector_base<T, A>::Vector_base(Vector_base&& a)
    : alloc{a.alloc}, elem{a.elem},
      sz{a.sz}, space{a.space}
{
    a.elem = nullptr;
    a.space = a.sz = 0;    
}

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector_base<T, A>& Vector_base<T, A>::operator=(Vector_base&& a)
{
    alloc.deallocate(elem, space);  // Освобождение старой памяти
    elem = a.elem;                  // Копируем elem, sz и space из a
    sz = a.sz;
    space = a.space;

    a.elem = nullptr;               // Делаем a пустым
    a.space = a.sz = 0;
    return *this;                   // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector_base<T, A>& Vector_base<T, A>::operator=(const Vector_base& a)
// Похож на конструктор копирования,
// но мы должны разобраться со старыми элементами
{
    if (this == &a) return *this;   // Самоприсваивание, ничего не делаем
    if (a.sz <= space) {            // Памяти достаточно, новая не нужна
        sz = a.sz;
        return *this;               // Возврат ссылки на себя
    }

    T* p{alloc.allocate(a.sz)};     // Выделение памяти
    alloc.deallocate(elem, space);  // Освобождение памяти

    space = sz = a.sz;              // Устанавливаем новый размер
    elem = p;                       // Переназначение указателя
    return *this;                   // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

#endif // VECTOR_BASE_HPP

//------------------------------------------------------------------------------
