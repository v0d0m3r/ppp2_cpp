//------------------------------------------------------------------------------

#ifndef SLIST_HPP
#define SLIST_HPP

//------------------------------------------------------------------------------

#include "Slist_base.hpp"

//------------------------------------------------------------------------------

template<typename Elem, typename A = Allocator<Link<Elem>>>
class Slist : private Slist_base<Elem, A>
{    
public:
    using size_type = size_t;
    using value_type = Elem;
    using reference = Elem&;
    using const_reference = const Elem&;

    Slist() : Slist_base<Elem, A>(), sz{0}  {}
    explicit Slist(size_type s);
    Slist(initializer_list<Elem> inlst);
    // Копирующие конструктор и присваивание
    Slist(const Slist& a);
    Slist& operator=(const Slist& a);
    // Перемещающие конструктор и присваивание
    Slist(Slist&& a) : Slist_base<Elem, A>{move(a)}, sz{a.sz} {}
    Slist& operator=(Slist&& a);
    ~Slist();                  // Деструктор

    class iterator;   // Тип-член класса: iterator

    Iterator<Slist<Elem, A>> begin(); // Итератор, указывающий на первый элемент
    Iterator<Slist<Elem, A>> end();   // Итератор, указывающий на элемент,
                      // следующий за последним
    Iterator<Slist<Elem, A>> begin() const;
    Iterator<Slist<Elem, A>> end() const;

    Iterator<Slist<Elem, A>> insert(iterator p,    // Вставка v в список
                                   const Elem& v); // перед элементом, на который
                                                   // указывает итератор p
    Iterator<Slist<Elem, A>> erase(iterator p);    // Удаление из списка элемента
                                                   // на который указывает p
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
    size_type size() const { return sz; }   // Количество элементов

private:
    size_type sz;

    template<template<class, class...> class C, class... Args>
    void init_from_contaner(const C<Elem, Args...>& c);
    void destroy();
};

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Slist<Elem, A>::Slist(size_type s) : Slist_base<Elem, A>{A()}, sz{s}
{
    if (s <= 0) return;
    Link<Elem> def;
    Link<Elem>* curr{this->first};
    for (size_type i{0}; i < s; ++i) {
        if (i == 0) {
            uninitialized_copy(&def, &def + 1, curr);
            continue;
        }
        Slist_base<Elem, A> n{this->alloc};
        uninitialized_copy(&def, &def + 1, n.first);

        curr->succ = n.first;
        curr = n.release();
    }
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Slist<Elem, A>::Slist(initializer_list<Elem> inlst)
    : Slist_base<Elem, A>{A()}, sz{inlst.size()}
{
    init_from_contaner(inlst);
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Slist<Elem, A>::Slist(const Slist<Elem, A>& a)
    : Slist_base<Elem, A>{a}, sz{a.sz}
{
    init_from_contaner(a);
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
template<template<class, class...> class C, class... Args>
void Slist<Elem, A>::init_from_contaner(const C<Elem, Args...>& c)
{
    if (c.size() == 0) return;
    // Инициализация элементов
    Link<Elem>* curr{nullptr};
    bool is_first{true};
    for (const auto& v : c) {
        Link<Elem> def{v};
        if (is_first) {
            uninitialized_copy(&def, &def + 1, this->first);
            curr = this->first;
            is_first = false;
            continue;
        }

        Slist_base<Elem, A> n{this->alloc};
        uninitialized_copy(&def, &def + 1, n.first);

        curr->succ = n.first;
        curr = n.release();
    }
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Slist<Elem, A>& Slist<Elem, A>::operator=(const Slist& a)
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

template<typename Elem, typename A>
Slist<Elem, A>& Slist<Elem, A>::operator=(Slist&& a)
{
    destroy();

    Slist_base<Elem, A> b{move(a)};
    sz = a.sz;
    swap<Slist_base<Elem, A>>(*this, b);    // Обмен представлений
    return *this;                           // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
class Slist<Elem, A>::iterator {
    Link<Elem>* curr;   // Текущий узел
public:
    using difference_type = ptrdiff_t;
    using value_type = Link<Elem>;
    using pointer = Link<Elem>*;
    using reference = Link<Elem>&;
    using iterator_category = forward_iterator_tag;

    friend class Slist;
    iterator(Link<Elem>* p) : curr{p} {}

    // Вперед:
    iterator& operator++() { curr = curr->succ; return *this; }

    // Разыменование (получение значения):
    Elem& operator*() { return curr->val; }

    bool operator==(const iterator& b) const
        { return curr == b.curr; }
    bool operator!=(const iterator& b) const
        { return curr != b.curr; }
};

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Iterator<Slist<Elem, A>> Slist<Elem, A>::begin()
{
    return iterator{this->first};
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Iterator<Slist<Elem, A>> Slist<Elem, A>::end()
{
    return iterator{nullptr};
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Iterator<Slist<Elem, A>> Slist<Elem, A>::begin() const
{
    return iterator{this->first};
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Iterator<Slist<Elem, A>> Slist<Elem, A>::end() const
{
    return iterator{nullptr};
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Iterator<Slist<Elem, A>> Slist<Elem, A>::insert(iterator p, const Elem &v)
{
    if (p == end() || p.curr == nullptr) return p;

    Link<Elem> lnk{v, p.curr};
    Slist_base<Elem, A> b{this->alloc};
    uninitialized_copy(&lnk, &lnk + 1, b.first);

    for (auto i{begin()}; i != end(); ++i) {
        if (i.curr == p.curr) {         // Вставляем перед first?
            this->first = b.first;
            break;
        }
        if (i.curr->succ == p.curr) {
            i.curr->succ = b.first;     // b следует за
            break;                      // предшественником p
        }
    }
    ++sz;
    return iterator{b.release()};
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Iterator<Slist<Elem, A>> Slist<Elem, A>::erase(iterator p)
// Удаление из списка элемента, находящегося в узле p
// Предусловия: требуется аргумент - итератор на элемент списка
// (неравный пустому узлу или end())
// Постусловия: возвращает итератор, указывающий на элемент,
// следующий за последним удаленным элементом,
// или p
{
    if (p == end() || p.curr == nullptr) return p;
    Slist_base<Elem, A> lnk{p.curr};
    ++p;                            // Переводим p на следующий узел

    for (auto i{begin()}; i != end(); ++i)
        if (i.curr->succ == lnk.first) {
            i.curr->succ = lnk.first->succ;
            break;
        }

    if (lnk.first == this->first)   // Если удаляем первый узел,
        this->first = p.curr;       // то переводим first на p
    this->alloc.destroy(lnk.first);
    --this->sz;
    return p;
}

//------------------------------------------------------------------------------

// Неэффективное добавление элемента в конец списка
template<typename Elem, typename A>
void Slist<Elem, A>::push_back(const Elem& v)
{
    auto p{begin()};
    advance(p, sz ? sz-1 : 0);

    Link<Elem> lnk{v};
    Slist_base<Elem, A> b{this->alloc};
    uninitialized_copy(&lnk, &lnk + 1, b.first);

    if (begin() == end()) this->first = b.release();
    else p.curr->succ = b.release();
    ++sz;
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
void Slist<Elem, A>::push_front(const Elem& v)
{
    Link<Elem> lnk{v, this->first};
    Slist_base<Elem, A> b{this->alloc};
    uninitialized_copy(&lnk, &lnk + 1, b.first);

    this->first = b.release();
    ++sz;
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
void Slist<Elem, A>::pop_front()
{
    erase(begin());
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
void Slist<Elem, A>::pop_back()
{
    auto p{begin()};
    advance(p, sz ? sz-1 : 0);
    erase(p);
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
void Slist<Elem, A>::destroy()
{
    auto p{begin()};
    auto last{end()};
    if (p == last) return;
    ++p;
    while (p != last) {
        Slist_base<Elem, A> b{p.curr};
        ++p;
        this->alloc.destroy(b.first);
    }
    this->alloc.destroy(this->first);
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
typename Slist<Elem, A>::reference Slist<Elem, A>::back()
{
    auto p{begin()};
    advance(p, sz ? sz-1 : 0);
    return *p;
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
typename Slist<Elem, A>::const_reference Slist<Elem, A>::back() const
{
    auto p{begin()};
    advance(p, sz ? sz-1 : 0);
    return *p;
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Slist<Elem, A>::~Slist()
{
    destroy();
}

//------------------------------------------------------------------------------

#endif // SLIST_HPP

//------------------------------------------------------------------------------



