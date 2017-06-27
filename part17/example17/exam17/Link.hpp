/*#ifndef LINK_HPP
#define LINK_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class Link
{
public:
    string value;
    Link(const string& v, Link* p = nullptr, Link* s = nullptr)
        : value{v}, prev{p}, succ{s} {}

    Link* insert(Link* n); // Вставка n перед данным объектом
    Link* add(Link* n);    // Вставка n после данного объекта
    Link* erase();         // Удаление данного объекта из списка
    Link* find(const string& s);             // Поиск s в списке;
    const Link* find(const string& s) const {} // Поиск в
                                             // константном списке;
    Link* advance(int n) const;  // Переход на n позиций в списке;

    Link* next() const { return succ; }
    Link* previous() const { return prev; }
private:
    Link* prev;
    Link* succ;
};

//------------------------------------------------------------------------------

void print_all(Link *p);

//------------------------------------------------------------------------------

#endif // LINK_HPP*/
