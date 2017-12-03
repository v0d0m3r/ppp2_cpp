//------------------------------------------------------------------------------

#ifndef LIST_BASE_HPP
#define LIST_BASE_HPP

//------------------------------------------------------------------------------

#include "../../part19/main_vector/Allocator.hpp"

//------------------------------------------------------------------------------

template<typename Elem>
struct Link {
    Link() = default;
    Link(const Elem& e) : val{e} { }
    Link* prev{nullptr}; // Предыдущий узел
    Link* succ{nullptr}; // Следующий узел
    Elem val;            // Значение
};

//------------------------------------------------------------------------------

template<typename Elem, typename A>
inline void deallocate_link(Link<Elem>* link)
{   // need use bind for this deleter!
    if (link) {
        A alloc;
        alloc.deallocate(link, 1);
    }
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Link<Elem>* allocate_link(A* alloc)
{
    return (alloc) ? alloc->allocate(1) : nullptr;
}

//------------------------------------------------------------------------------

template<typename Elem, typename A = Allocator<Link<Elem>>>
using Link_ptr = unique_ptr<Link<Elem>, decltype(&deallocate_link<Elem, A>)>;

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Link_ptr<Elem, A> make_link_ptr(A* a)
{
    return Link_ptr<Elem, A> {
        allocate_link<Elem, A>(a), deallocate_link<Elem, A>
    };
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Link_ptr<Elem, A> make_link_ptr(Link<Elem>* pointer)
{
    return Link_ptr<Elem, A> {
        pointer, deallocate_link<Elem, A>
    };
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
struct List_base {
    A alloc;    // Распределитель памяти
    Link_ptr<Elem, A> first;
    Link_ptr<Elem, A> last;
    int sz;     // Количество элементов

    List_base();
    List_base(const A& a, int size);

    // Копирующие конструктор и присваивание
    List_base(const List_base &a) : List_base{a.alloc, a.sz} {}
    List_base& operator=(const List_base& a);

    // Перемещающие конструктор и присваивание
    List_base(List_base&& a);
    List_base& operator=(List_base&& a);
};

//------------------------------------------------------------------------------

template<typename Elem, typename A>
List_base<Elem, A>::List_base()
    : alloc{A{}},
      first{make_link_ptr<Elem, A>(nullptr)},
      last {make_link_ptr<Elem, A>(nullptr)}, sz{0}
{
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
List_base<Elem, A>::List_base(const A& a, int size)
    : alloc{a},
      first{make_link_ptr<Elem, A>(size>0 ? &alloc : nullptr)},
      last {make_link_ptr<Elem, A>(size>0 ? &alloc : nullptr)},
      sz{size}
{}

//------------------------------------------------------------------------------

template<typename T, typename A>
List_base<T, A>::List_base(List_base&& a)
    : alloc{a.alloc},
      first{move(a.first)}, last{move(a.last)},
      sz{a.sz}
{
    a.sz = 0;
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
List_base<Elem, A>& List_base<Elem, A>::operator=(List_base&& a)
{
    first = move(a.first);
    last = move(a.last);
    sz = a.sz;

    a.sz = 0;
    return *this;               // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
List_base<Elem, A>& List_base<Elem, A>::operator=(const List_base& a)
// Похож на конструктор копирования,
// но мы должны разобраться со старыми элементами
{
    if (this == &a) return *this;   // Самоприсваивание, ничего не делаем
    first = move(make_link_ptr<Elem, A>(a.sz > 0 ? &alloc : nullptr));
    last  = move(make_link_ptr<Elem, A>(a.sz > 0 ? &alloc : nullptr));
    sz = a.sz;
    return *this;                   // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

#endif // LIST_BASE_HPP

//------------------------------------------------------------------------------
