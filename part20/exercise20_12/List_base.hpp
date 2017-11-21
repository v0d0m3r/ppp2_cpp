//------------------------------------------------------------------------------

#ifndef LIST_BASE_HPP
#define LIST_BASE_HPP

//------------------------------------------------------------------------------

#include "../../part19/main_vector/Allocator.hpp"

//------------------------------------------------------------------------------

template<typename Elem>
struct Link {
    Link* prev{nullptr}; // Предыдущий узел
    Link* succ{nullptr}; // Следующий узел
    Elem val;            // Значение
};

//------------------------------------------------------------------------------

template<typename Elem, typename A>
struct List_base {
    A alloc;    // Распределитель памяти
    Link<Elem>* first;
    Link<Elem>* last;
    int sz;     // Количество элементов

    List_base() : alloc{A{}}, first{nullptr}, last{nullptr}, sz{0} {}
    List_base(const A& a, int size) {}

    // Копирующие конструктор и присваивание
    List_base(const List_base &a) : List_base{a.alloc, a.sz} {}
    List_base& operator=(const List_base& a) {}

    // Перемещающие конструктор и присваивание
    List_base(List_base&& a);
    List_base& operator=(List_base&& a);

    ~List_base();

    Link<Elem>* get_link_ptr() { return alloc.allocate(1); }
    void put_link_ptr(Link<Elem>* l) { alloc.deallocate(l, 1); }
};

//------------------------------------------------------------------------------

/*template<typename Elem, typename A>
List_base<Elem, A>::List_base(const A& a, int size)
    : alloc{a},
      first{size>0 ? get_link_ptr(): nullptr},
      last {size>0 ? get_link_ptr(): nullptr},
      sz{size}
{}*/

//------------------------------------------------------------------------------

template<typename Elem, typename A>
List_base<Elem, A>::~List_base()
{
    put_link_ptr(first);
    put_link_ptr(last);
}

//------------------------------------------------------------------------------

template<typename T, typename A>
List_base<T, A>::List_base(List_base&& a)
    : alloc{a.alloc},
      first{a.first}, last{a.last},
      sz{a.sz}
{
    a.first = nullptr;
    a.last = nullptr;
    a.sz = 0;
}

//------------------------------------------------------------------------------

template<typename T, typename A>
List_base<T, A>& List_base<T, A>::operator=(List_base&& a)
{
    first = a.first;
    last = a.last;
    sz = a.sz;

    a.first = a.last = nullptr; // Делаем a пустым
    a.sz = 0;
    return *this;               // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

template<typename T, typename A>
List_base<T, A>& List_base<T, A>::operator=(const List_base& a)
// Похож на конструктор копирования,
// но мы должны разобраться со старыми элементами
{
    if (this == &a) return *this;   // Самоприсваивание, ничего не делаем



    return *this;                   // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

#endif // LIST_BASE_HPP

//------------------------------------------------------------------------------
