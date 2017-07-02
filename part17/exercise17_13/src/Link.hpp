#ifndef LINK_HPP
#define LINK_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

struct God {
    God(const string& n, const string& m = "none",
        const string& v = "none", const string& w = "none")
        : name{n}, myth{m}, veh{v}, weap{w} {}

    string name;
    string myth;
    string veh;
    string weap;
};

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const God& g);

//------------------------------------------------------------------------------

class Link
{
public:
    God god;
    Link(const God& g, Link* p = nullptr, Link* s = nullptr)
        : god{g}, prev{p}, succ{s} {}

    Link* insert(Link* n); // Вставка n перед данным объектом
    Link* add(Link* n);    // Вставка n после данного объекта
    Link* erase();         // Удаление данного объекта из списка
    void clear_connect()   // Обрывает связи со списком
    { prev = nullptr; succ = nullptr; }
    Link* find(const string& s);             // Поиск s в списке;
    const Link* find(const string& s) const; // Поиск в
                                             // константном списке;
    Link* advance(int n) const; // Переход на n позиций в списке;
    Link* add_ordered(Link* n); // Вставка n в правильной
                                // лексикографической позиции
    Link* next() const { return succ; }
    Link* previous() const { return prev; }

private:
    Link* prev;
    Link* succ;
};

//------------------------------------------------------------------------------
// Извлекает s из списка l
pair<Link*, Link*> extract(Link* l, const string& s);
void print_all(Link *p);

//------------------------------------------------------------------------------

#endif // LINK_HPP
