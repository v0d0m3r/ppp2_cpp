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
    string value;
    int key;

    explicit Link(int ll)
        : key{0}, l{ll}, succ{new Link*[l]{nullptr}} {}
    Link(const string& v, int k, int ll)
        : value{v}, key{k}, l{ll}, succ{new Link*[l]{nullptr}} {}
    ~Link() { delete[] succ;}

    int level() const { return l; }
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
    Skip_list(int mm, Link* c = nullptr);

    //Link* find(int key);
    //void insert(Link* n);

private:
    int m;    // Максимально возможное количество узлов
    int l{0}; // Уровень списка - максимальный уровень узла

    Link* head;
    Link* curr;
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
