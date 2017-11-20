//------------------------------------------------------------------------------

#ifndef LIST_HPP
#define LIST_HPP

//------------------------------------------------------------------------------

#include "List_base.hpp"

//------------------------------------------------------------------------------

template<typename Elem>
class List {
public:
    List() {}

    template<typename T> class Link;
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

    Elem& front();                  // Первый элемент
    Elem& back();                   // Последний элемент
private:
    int sz;     // Количество элементов
    Link<Elem>* first;
    Link<Elem>* last;
};

//------------------------------------------------------------------------------

template<typename Elem>
template<typename T>
class List<Elem>::Link {
public:
    Link* prev; // Предыдущий узел
    Link* succ; // Следующий узел
    Elem val;   // Значение
};

//------------------------------------------------------------------------------

template<typename Elem>
class List<Elem>::iterator {
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

#endif // LIST_HPP



