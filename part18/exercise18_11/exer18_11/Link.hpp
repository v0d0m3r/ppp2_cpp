#ifndef LINK_HPP
#define LINK_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

struct List;

//------------------------------------------------------------------------------

class Link
{
public:
    int key;
    string value;
    Link() : key{0}, w{0}, succ{nullptr} {}
    Link(int k, const string& v, int ww)
        : key{k}, value{v}, w{ww}, succ{new Link*[w]{nullptr}} {}
    ~Link() { delete[] succ;}
    int level() const { return w; }
    Link* next(int i) const { return succ[i]; }
    void set_next(int i, Link* s) { succ[i] = s; }
private:
    int l;
    Link** succ;
};

//------------------------------------------------------------------------------

class Skip_list
{
public:
    Skip_list();

private:
    Link* h;
    Link* c;

    int m;    // Максимально возможное количество узлов
    int l;    // Уровень списка - максимальный уровень узла
};

//------------------------------------------------------------------------------

/*struct List {
    List(Link* h = nullptr)
        : head{h} {}

    Link* head;
};*/

//------------------------------------------------------------------------------

/*void print_all(Link *p);
void print_all(List* h);*/

//------------------------------------------------------------------------------

#endif // LINK_HPP
