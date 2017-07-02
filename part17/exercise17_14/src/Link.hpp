#ifndef LINK_HPP
#define LINK_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

struct List {
    List(Link* h = nullptr)
        : head{h} {}

    Link* head;
};

//------------------------------------------------------------------------------

class Link
{
public:
    string value;
    Link(const string& v, Link* s = nullptr)
        : value{v}, succ{s} {}

    Link* insert(List* h, Link* n); // Вставка n перед данным объектом
    Link* add(List* h, Link* n);    // Вставка n после данного объекта
    Link* erase(List* h);         // Удаление данного объекта из списка
    Link* find(List* h, const string& s);             // Поиск s в списке;
    const Link* find(List* h, const string& s) const; // Поиск в
                                             // константном списке;
    Link* advance(List* h, int n) const;  // Переход на n позиций в списке;

    Link* next() const { return succ; }   
private:
    Link* succ;
};

//------------------------------------------------------------------------------

void print_all(Link *p);

//------------------------------------------------------------------------------

#endif // LINK_HPP
