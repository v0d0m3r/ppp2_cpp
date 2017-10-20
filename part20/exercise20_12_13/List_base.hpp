//------------------------------------------------------------------------------

#ifndef LIST_BASE_HPP
#define LIST_BASE_HPP

//------------------------------------------------------------------------------

#include "../../part19/main_vector/Allocator.hpp"

//------------------------------------------------------------------------------

template<typename Elem>
struct Link {
    Link* prev; // Предыдущий узел
    Link* succ; // Следующий узел
    Elem val;   // Значение
};

//------------------------------------------------------------------------------

template<typename Elem, typename A>
struct List_base {
    A alloc;    // Распределитель памяти
    Link<Elem>* first;
    Link<Elem>* last;
    int sz;     // Количество элементов
    int space;  // Размер выделенной памяти

    List_base() : alloc{A{}}, first{nullptr}, last{nullptr}, sz{0}, space{0} {}
    List_base(const A& a, int size, int n = 0);

    // Копирующие конструктор и присваивание
    List_base(const List_base &a) : List_base{a.alloc, a.sz} {}
    List_base& operator=(const List_base& a);

    // Перемещающие конструктор и присваивание
    List_base(List_base&& a);
    List_base& operator=(List_base&& a);

    ~List_base();
};

//------------------------------------------------------------------------------

List_base(const A& a, int size, int n = 0);

//------------------------------------------------------------------------------

#endif // LIST_BASE_HPP

//------------------------------------------------------------------------------
