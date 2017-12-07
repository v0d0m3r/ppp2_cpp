//------------------------------------------------------------------------------

#ifndef LIST_HPP
#define LIST_HPP

//------------------------------------------------------------------------------

#include "List_base.hpp"

//------------------------------------------------------------------------------

template<typename Elem, typename A = Allocator<Link<Elem>>>
class List : private List_base<Elem, A>
{
    int sz;
public:
    using size_type = size_t;
    using value_type = Elem;

    List() : List_base<Elem, A>()  {}
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

    Elem& front()                   // Первый элемент
        { return this->first->val; }
    Elem& back()                    // Последний элемент
        { return this->last->prev; }

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
};

//------------------------------------------------------------------------------

template<typename Elem, typename A>
List<Elem, A>::List(size_type s) : List_base<Elem, A>{A()}, sz{s}
{
    if (s <= 0) return;
    Link<Elem> def;
    Link<Elem>* curr{this->first};
    for (int i=0; i < s; ++i) {
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
        for (; p != end(); ++p) erase(p); // Удаляем новые узлы
    }
    return *this;                         // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
class List<Elem, A>::iterator {
    Link<Elem>* curr;   // Текущий узел
public:
    using difference_type = ptrdiff_t;
    using value_type = Link<Elem>;
    using pointer = Link<Elem>*;
    using reference = Link<Elem>&;
    using iterator_category = bidirectional_iterator_tag;

    friend class List;
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
Iterator<List<Elem, A>> List<Elem, A>::begin()
{
    return iterator{this->first};
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Iterator<List<Elem, A>> List<Elem, A>::end()
{
    return iterator{nullptr};
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Iterator<List<Elem, A>> List<Elem, A>::begin() const
{
    return iterator{this->first};
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
Iterator<List<Elem, A>> List<Elem, A>::end() const
{
    return iterator{nullptr};
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
    ++this->sz;
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
    /*if (p == end() || p.curr == nullptr) return p;
    if (this->sz == 1) {                 // Очистка списка
        if (p.curr != this->first.get()) // Итератор не из
            return p;                    // этой последовательности

        if (this->first) this->alloc.destroy(this->first.get());
        if (this->last)  this->alloc.destroy(this->last.get());
        this->first.reset(nullptr);
        this->last.reset(nullptr);
        this->sz = 0;
        return begin();
    }

    Link_ptr<Elem, A> l{make_link_ptr<Elem, A>(p.curr)};
    if (l->succ) l->succ->prev = l->prev;
    if (l->prev) l->prev->succ = l->succ;

    if (l.get() == this->first.get()) {
        this->first.release();
        this->first.reset(l->succ);
    }
    iterator succ{l->succ};
    this->alloc.destroy(l.get());
    --this->sz;
    return succ;*/
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
void List<Elem, A>::push_back(const Elem& v)
{
    /*if (this->sz == 0) {
        ++this->sz;
        reserve(v);
        return;
    }
    Link_ptr<Elem, A> n{make_link_ptr<Elem, A>(&this->alloc)};
    Link<Elem> lnk{Link<Elem>{v}};

    uninitialized_copy(&lnk, &lnk + 1, n.get());

    if (this->last->prev)                 // n следует за
        this->last->prev->succ = n.get(); // предшественником last
    n->succ = this->last.get();           // Последующий n становится
                                          // last
    n->prev = this->last->prev;           // Предшественник last
                                          // становится предшественником n
    this->last->prev = n.get();           // n предшествует last
    n.release();
    ++this->sz;*/
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
void List<Elem, A>::push_front(const Elem& v)
{
    /*if (this->sz == 0) {
        ++this->sz;
        reserve(v);
        return;
    }
    Link_ptr<Elem, A> n{make_link_ptr<Elem, A>(&this->alloc)};
    Link<Elem> lnk{Link<Elem>{v}};
    uninitialized_copy(&lnk, &lnk + 1, n.get());

    n->succ = this->first.get();
    this->first->prev = n.get();

    swap(this->first, n);
    n.release();
    ++this->sz;*/
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
    auto p{end()};
    if (begin() == p) return;
    --p;
    erase(p);
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
void List<Elem, A>::reserve(const Elem& v)
{
    List_base<Elem, A> b{this->alloc, this->sz};

    Link<Elem> def{v};
    uninitialized_copy(&def, &def + 1, b.first.get());
    uninitialized_copy(&def, &def + 1, b.last.get());

    b.first->succ = b.last.get();
    b.last->prev = b.first.get();
    swap<List_base<Elem, A>>(*this, b);      // Обмен представлений
}

//------------------------------------------------------------------------------

template<typename Elem, typename A>
void List<Elem, A>::destroy()
{
    auto p{begin()};
    auto last{end()};
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
List<Elem, A>::~List()
{
    destroy();
}

//------------------------------------------------------------------------------

#endif // LIST_HPP

//------------------------------------------------------------------------------


