//------------------------------------------------------------------------------

#ifndef LIST_BASE_HPP
#define LIST_BASE_HPP

//------------------------------------------------------------------------------

#include "../../part19/main_vector/Allocator.hpp"

//------------------------------------------------------------------------------

template<typename Elem>
struct Link {
    Link(const Elem& v = Elem{}, Link* p = nullptr, Link* s = nullptr)
        : val{v}, prev{p}, succ{s} {}

    Link* prev; // Предыдущий узел
    Link* succ; // Следующий узел
    Elem val;   // Значение
};

//------------------------------------------------------------------------------

template<typename Elem, typename A>
struct List_base {
    A alloc;    // Распределитель памяти
    Link<Elem>* first;

    List_base() : alloc{A{}}, first{nullptr} {}
    List_base(Link<Elem>* f) : alloc{A{}}, first{f} {}
    List_base(const A& a) : alloc{a}, first{alloc.allocate(1)} {}

    // Копирующие конструктор и присваивание
    List_base(const List_base &a) : List_base{a.alloc} {}
    List_base& operator=(const List_base& a);

    // Перемещающие конструктор и присваивание
    List_base(List_base&& a) : alloc{a.alloc}, first{a.first}
        { a.first = nullptr; }
    List_base& operator=(List_base&& a);

    ~List_base() { alloc.deallocate(first, 1); }

    Link<Elem>* release()
        { Link<Elem>* tmp{first}; first = nullptr; return tmp; }
};

//------------------------------------------------------------------------------

template<typename Elem, typename A>
List_base<Elem, A>& List_base<Elem, A>::operator=(List_base&& a)
{
    alloc.deallocate(first, 1);
    first = a.first;

    a.first = nullptr;
    return *this;               // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
List_base<Elem, A>& List_base<Elem, A>::operator=(const List_base& a)
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

#endif // LIST_BASE_HPP

//------------------------------------------------------------------------------
