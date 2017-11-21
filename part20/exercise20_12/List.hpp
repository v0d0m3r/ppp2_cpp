//------------------------------------------------------------------------------

#ifndef LIST_HPP
#define LIST_HPP

//------------------------------------------------------------------------------

#include "List_base.hpp"

//------------------------------------------------------------------------------

template<typename Elem, typename A = Allocator<Link<Elem>>>
class List : private List_base<Elem, A>
{
public:
    List() : List_base<Elem, A>()  {}
    explicit List(int s);

     ~List();                  // Деструктор

    class iterator;   // Тип-член класса: iterator

    iterator begin(); // Итератор, указывающий на первый элемент
    iterator end();   // Итератор, указывающий на элемент,
                      // следующий за последним
    iterator insert(iterator p,     // Вставка v в список
                    const Elem& v); // после элемента, на который
                                    // указывает итератор p
    iterator erase(iterator p);     // Удаление из списка элемента
                                    // на который указывает итератор p
    void push_back(const Elem& v);  // Вставка v в конец списка
    void push_front(const Elem& v); // Вставка v в начало списка
    void pop_front();               // Удаление первого элемента
    void pop_back();                // Удаление последнего элемента

    Elem& front()                   // Первый элемент
        { return this->first->val; }
    Elem& back()                    // Последний элемент
        { return this->last->prev; }
};

//------------------------------------------------------------------------------

template<typename Elem, typename A = Allocator<Link<Elem>>>
inline void deallocate_lnk(Link<Elem>* l)
{
    A aloc;
    aloc.deallocate(l, 1);
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
List<Elem, A>::List(int s) : List_base<Elem, A>{A(), s}
{
    if (s <= 0) return;

    Link<Elem> def{Link<Elem>{}};
    uninitialized_copy(&def, &def + 1, this->first);
    uninitialized_copy(&def, &def + 1, this->last);

    Link<Elem>* curr{this->first};

    for (int i=1; i < s; ++i) {
        unique_ptr<Link<Elem>, void(*)(Link<Elem>*)>
                n = {this->get_link_ptr(), deallocate_lnk};

        uninitialized_copy(&def, &def + 1, n.get());

        n->prev = curr;
        curr->succ = n.get();
        curr = n.release();
    }
    curr->succ = this->last;
    this->last->prev = curr;
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
class List<Elem, A>::iterator {
    Link<Elem>* curr;   // Текущий узел
public:
    iterator(Link<Elem>* p) : curr{p} {}

    // Вперед:
    iterator& operator++() { curr = curr->succ; return *this; }

    // Назад:
    iterator& operator--() { curr = curr->prev; return *this; }

    // Разыменование (получение значения):
    Elem& operator*() { return curr->val; }

    bool operator==(const iterator& b) const
        { return curr == b.curr; }
    bool operator!=(const iterator& b) const
        { return curr != b.curr; }
};

//------------------------------------------------------------------------------

template<typename Elem, typename A>
List<Elem, A>::~List()
{
    Link<Elem>* p{nullptr};
    Link<Elem>* curr{this->first ? this->first->succ : nullptr};
    while (curr != this->last) {
        p = curr->succ;
        this->alloc.destroy(curr);
        this->put_link_ptr(curr);
        curr = p;
    }
    if (this->first && this->last) {
        this->alloc.destroy(this->first);
        this->alloc.destroy(this->last);
    }
}

//------------------------------------------------------------------------------

#endif // LIST_HPP

//------------------------------------------------------------------------------



