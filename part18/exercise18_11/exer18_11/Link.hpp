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
    ~Skip_list() { delete[] h; }

    //Link* find(int key);
    Link* insert(Link* n);

    int max_level() const { return m; }
    int level()     const { return l; }
    int count()     const { return cnt; }
    Link* head()    const { return h; }
    Link* current() const { return curr; }

protected:
    void set_level(int ll) { l = ll; }

private:
    int m;    // Максимально возможное количество узлов
    int l{0}; // Уровень списка - максимальный уровень узла
    int cnt{0};
    Link* h;
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
