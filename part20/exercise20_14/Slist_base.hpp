//------------------------------------------------------------------------------

#ifndef SLIST_BASE_HPP
#define SLIST_BASE_HPP

//------------------------------------------------------------------------------

#include "../../part19/main_vector/Allocator.hpp"

//------------------------------------------------------------------------------

template<typename Elem>
struct Link {
    Link(const Elem& v = Elem{}, Link* s = nullptr)
        : succ{s}, val{v}   {}

    Link* succ; // Следующий узел
    Elem val;   // Значение
};

//------------------------------------------------------------------------------

template<typename Elem, typename A>
struct Slist_base {
    A alloc;    // Распределитель памяти
    Link<Elem>* first;

    Slist_base() : alloc{A{}}, first{nullptr} {}
    Slist_base(Link<Elem>* f) : alloc{A{}}, first{f} {}
    Slist_base(const A& a) : alloc{a}, first{alloc.allocate(1)} {}

    // Копирующие конструктор и присваивание
    Slist_base(const Slist_base &a) : Slist_base{a.alloc} {}
    Slist_base& operator=(const Slist_base& a);

    // Перемещающие конструктор и присваивание
    Slist_base(Slist_base&& a) : alloc{a.alloc}, first{a.first}
        { a.first = nullptr; }
    Slist_base& operator=(Slist_base&& a);

    ~Slist_base() { alloc.deallocate(first, 1); }

    Link<Elem>* release()
        { Link<Elem>* tmp{first}; first = nullptr; return tmp; }
};

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Slist_base<Elem, A>& Slist_base<Elem, A>::operator=(Slist_base&& a)
{
    alloc.deallocate(first, 1);
    first = a.first;

    a.first = nullptr;
    return *this;               // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Slist_base<Elem, A>& Slist_base<Elem, A>::operator=(const Slist_base& a)
// Похож на конструктор копирования,
// но мы должны разобраться со старыми элементами
{
    if (this == &a) return *this;     // Самоприсваивание, ничего не делаем
    Link<Elem>* p{alloc.allocate(1)}; // Выделение новой памяти
    alloc.deallocate(first, 1);       // Освобождение старой памяти

    first = p;                        // Переназначение указателя
    return *this;                     // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

#endif // SLIST_BASE_HPP

//------------------------------------------------------------------------------
