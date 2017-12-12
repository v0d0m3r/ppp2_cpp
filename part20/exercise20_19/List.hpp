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
    using size_type = size_t;
    using value_type = Elem;
    using reference = Elem&;
    using const_reference = const Elem&;
    using pointer = Elem*;

    List() : List_base<Elem, A>(), sz{0}  {}
    explicit List(size_type s);
    List(initializer_list<Elem> inlst);
    // Копирующие конструктор и присваивание
    List(const List& a);
    List& operator=(const List& a);
    List(List&& a) : List_base<Elem, A>{move(a)} {}
    ~List();                  // Деструктор

    class iterator;   // Тип-член класса: iterator

    Iterator<List<Elem, A>> begin(); // Итератор, указывающий на первый элемент
    Iterator<List<Elem, A>> end();   // Итератор, указывающий на элемент,
                      // следующий за последним
    Iterator<List<Elem, A>> begin() const;
    Iterator<List<Elem, A>> end() const;

    Iterator<List<Elem, A>> insert(iterator p,     // Вставка v в список
                                   const Elem& v); // после элемента, на который
                                    // указывает итератор p
    Iterator<List<Elem, A>> erase(iterator p);     // Удаление из списка элемента
                                    // на который указывает итератор p
    void push_back(const Elem& v);  // Вставка v в конец списка
    void push_front(const Elem& v); // Вставка v в начало списка
    void pop_front();               // Удаление первого элемента
    void pop_back();                // Удаление последнего элемента

    reference front()                   // Первый элемент
        { return this->first->val; }
    const_reference front() const
        { return this->first->val; }
    reference back();                   // Последний элемент
    const_reference back() const;

    size_type size() const { return this->sz; }   // Количество элементов
    void reserve(const Elem& v = Elem{});

    template<template<class, class...> class C, class... Args>
    void init_from_contaner(const C<Elem, Args...>& c)
    {
        if (c.size() == 0) return;
        // Инициализация элементов
        Link<Elem>* curr{nullptr};
        bool is_first{true};
        for (const auto& v : c) {
            Link<Elem> def{v, curr};
            if (is_first) {
                uninitialized_copy(&def, &def + 1, this->first);
                curr = this->first;
                is_first = false;
                continue;
            }

            List_base<Elem, A> n{this->alloc};
            uninitialized_copy(&def, &def + 1, n.first);

            curr->succ = n.first;
            curr = n.release();
        }
    }
    void destroy();

private:
    size_type sz;
};

//------------------------------------------------------------------------------

template<typename Elem, typename A>
List<Elem, A>::List(size_type s) : List_base<Elem, A>{A()}, sz{s}
{
    if (s <= 0) return;
    Link<Elem> def;
    Link<Elem>* curr{this->first};
    for (size_type i{0}; i < s; ++i) {
        if (i == 0) {
            uninitialized_copy(&def, &def + 1, curr);
            continue;
        }
        List_base<Elem, A> n{this->alloc};
        uninitialized_copy(&def, &def + 1, n.first);

        n.first->prev = curr;
        curr->succ = n.first;
        curr = n.release();
    }
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
List<Elem, A>::List(initializer_list<Elem> inlst)
    : List_base<Elem, A>{A()}, sz{inlst.size()}
{
    init_from_contaner(inlst);
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
List<Elem, A>::List(const List<Elem, A>& a)
    : List_base<Elem, A>{a}, sz{a.sz}
{
    init_from_contaner(a);
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
List<Elem, A>& List<Elem, A>::operator=(const List& a)
// Похож на конструктор копирования,
// но мы должны разобраться со старыми элементами
{
    if (this == &a) return *this;         // Самоприсваивание,
                                          // ничего не делаем
    if (a.sz >= sz) {
        auto p{a.begin()};
        for (auto i{begin()}; i != end(); ++i, ++p)
            copy(&*p, &*p+1, &*i);        // Копируем элементы
                                          // в инциализированной памяти
        for (; p != a.end(); ++p)         // Добавляем новые узлы
            push_back(*p);
    }
    else {        
        auto p{copy(a.begin(), a.end(), begin())};
        while (p != end()) p = erase(p);  // Удаляем ненужные узлы
    }
    return *this;                         // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

template<typename Elem>
bool is_iterator(Link<Elem>* curr, Link<Elem>* first, Link<Elem>* last)
{
    if (curr == last) return true;
    for (; first; first = first->succ)
        if (first==curr) return true;
    return false;
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
class List<Elem, A>::iterator {
    Link<Elem>* curr;   // Текущий узел
    Link<Elem>* first;  // Первый узел
    Link<Elem>* last;   // Следующий за последним
public:
    using difference_type = ptrdiff_t;
    using value_type = Link<Elem>;
    using pointer = Link<Elem>*;
    using reference = Link<Elem>&;
    using iterator_category = bidirectional_iterator_tag;

    friend class List;

    iterator(Link<Elem>* cc = nullptr, Link<Elem>* ff = nullptr,
             Link<Elem>* ll = nullptr)
        : curr{cc}, first{ff}, last{ll}
    {
        if (!is_iterator(curr, first, last))
            error("iterator is not located between first and last");
    }

    // Вперед:
    iterator& operator++();

    // Назад:
    iterator& operator--();

    // Разыменование (получение значения):
    List<Elem, A>::reference operator*();

    bool operator==(const iterator& b) const
        { return curr == b.curr; }
    bool operator!=(const iterator& b) const
        { return curr != b.curr; }
};

//------------------------------------------------------------------------------

template<typename Elem, typename A>
typename List<Elem, A>::iterator& List<Elem, A>::iterator::operator++()
{
    if (curr == last) error("iterator& operator++(): out of range!");
    curr = curr->succ;
    return *this;
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
typename List<Elem, A>::iterator& List<Elem, A>::iterator::operator--()
{
    if (curr == first)
        error("iterator& operator--(): out of range!");
    curr = curr->prev;
    return *this;
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
typename List<Elem, A>::reference List<Elem, A>::iterator::operator*()
{
    if (curr == last)
        error("iterator& operator*: it is last node!");
    return curr->val;
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Iterator<List<Elem, A>> List<Elem, A>::begin()
{
    return iterator{this->first, this->first};
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Iterator<List<Elem, A>> List<Elem, A>::end()
{
    return iterator{};
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Iterator<List<Elem, A>> List<Elem, A>::begin() const
{
    return iterator{this->first, this->first};
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Iterator<List<Elem, A>> List<Elem, A>::end() const
{
    return iterator{};
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Iterator<List<Elem, A>> List<Elem, A>::insert(iterator p, const Elem &v)
{
    if (p == end() || p.curr == nullptr) return p;

    Link<Elem> lnk{v, p.curr, p.curr->succ};
    List_base<Elem, A> b{this->alloc};
    uninitialized_copy(&lnk, &lnk + 1, b.first);

    if (p.curr->succ)                   // b предшествует
        p.curr->succ->prev = b.first;   // последующему p
    p.curr->succ = b.release();         // b следует за p

    ++p;
    ++sz;
    return p;
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Iterator<List<Elem, A>> List<Elem, A>::erase(iterator p)
// Удаление из списка элемента, находящегося в узле p
// Предусловия: требуется аргумент - итератор на элемент списка
// (неравный пустому узлу или end())
// Постусловия: возвращает итератор, указывающий на элемент,
// следующий за последним удаленным элементом,
// или p
{
    if (p == end() || p.curr == nullptr) return p;
    List_base<Elem, A> lnk{p.curr};
    ++p;                            // Переводим p на следующий узел
    if (lnk.first->succ) lnk.first->succ->prev = lnk.first->prev;
    if (lnk.first->prev) lnk.first->prev->succ = lnk.first->succ;
    if (lnk.first == this->first)   // Если удаляем первый узел,
        this->first = p.curr;       // то переводим first на p
    this->alloc.destroy(lnk.first);
    --this->sz;
    return p;
}

//------------------------------------------------------------------------------

// Неэффективное добавление элемента в конец списка
template<typename Elem, typename A>
void List<Elem, A>::push_back(const Elem& v)
{
    auto p{begin()};
    advance(p, sz ? sz-1 : 0);

    Link<Elem> lnk{v, p.curr};
    List_base<Elem, A> b{this->alloc};
    uninitialized_copy(&lnk, &lnk + 1, b.first);

    if (begin() == end()) this->first = b.release();
    else p.curr->succ = b.release();
    ++sz;
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
void List<Elem, A>::push_front(const Elem& v)
{
    Link<Elem> lnk{v, nullptr, this->first};
    List_base<Elem, A> b{this->alloc};
    uninitialized_copy(&lnk, &lnk + 1, b.first);

    if (this->first) this->first->prev = b.first;
    this->first = b.release();
    ++sz;
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
void List<Elem, A>::pop_front()
{
    erase(begin());
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
void List<Elem, A>::pop_back()
{
    auto p{begin()};
    advance(p, sz ? sz-1 : 0);
    erase(p);
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
void List<Elem, A>::destroy()
{
    auto p{begin()};
    auto last{end()};
    if (p == last) return;
    ++p;
    while (p != last) {
        List_base<Elem, A> b{p.curr};
        ++p;
        this->alloc.destroy(b.first);
    }
    this->alloc.destroy(this->first);
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
typename List<Elem, A>::reference List<Elem, A>::back()
{
    auto p{begin()};
    advance(p, sz ? sz-1 : 0);
    return *p;
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
typename List<Elem, A>::const_reference List<Elem, A>::back() const
{
    auto p{begin()};
    advance(p, sz ? sz-1 : 0);
    return *p;
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
List<Elem, A>::~List()
{
    destroy();
}

//------------------------------------------------------------------------------

#endif // LIST_HPP

//------------------------------------------------------------------------------



