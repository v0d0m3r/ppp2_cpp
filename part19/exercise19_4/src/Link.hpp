//------------------------------------------------------------------------------

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

ostream& operator<<(ostream& os, const God& g)
{
    return os << '(' << g.name
              << ", " << g.myth
              << ", " << g.veh
              << ", " << g.weap << ')';
}

inline bool operator==(const God& a, const God& b)
{
    return a.name == b.name;
}

inline bool operator<(const God& a, const God& b)
{
    return a.name < b.name;
}

inline bool operator<=(const God& a, const God& b)
{
    return a.name <= b.name;
}

//------------------------------------------------------------------------------

template<typename T>
struct Link {
    T value;
    Link* prev;
    Link* succ;    
    Link(const T& v, Link* p = nullptr, Link* s = nullptr)
        : value{v}, prev{p}, succ{s} {}
};

//------------------------------------------------------------------------------

// Поиск v в списке;
// возврат nullptr, если не найдено v
template<typename T>
Link<T>* find(Link<T>* p, const T& v)
{
    while (p) {
        if (p->value == v) return p;
        p = p->succ;
    }
    return p;
}

//------------------------------------------------------------------------------

// Вставка n перед p; возврат n
template<typename T>
Link<T>* insert(Link<T>* p, Link<T>* n)
{
    if (n == nullptr) return p;
    if (p == nullptr) return n;

    n->succ = p;            // p сдедует за n
    if (p->prev)            // n следует после
        p->prev->succ = n;  // предшественника p

    n->prev = p->prev;      // Предшественник p становится
                            // предшественником n
    p->prev = n;            // n становится предшественником p
    return n;
}

//------------------------------------------------------------------------------

// Вставка n после p; возврат n
template<typename T>
Link<T>* add(Link<T>* p, Link<T>* n)
{
    if (n == nullptr) return p;
    if (p == nullptr) return n;

    n->succ = p->succ;      // Последующий p следует за n
    if (p->succ)            // Предшественником последующего p
        p->succ->prev = n;  // становится n

    n->prev = p;            // p становится
                            // предшественником n
    p->succ = n;            // n становится последующим p
    return n;
}

//------------------------------------------------------------------------------

// Вставка n в правильной
// лексикографической позиции
template<typename T>
Link<T>* add_ordered(Link<T>* p, Link<T>* n)
{
    if (n == nullptr) return p;
    if (p == nullptr) return n;

    if (n->value < p->value) return insert(p, n);

    Link<T>* ptr{p};
    while (ptr->value <= n->value) {
        if (ptr->succ == nullptr) {
            add(ptr, n);
            return p;
        }
        ptr = ptr->succ;
    }
    insert(ptr, n);
    return p;
}

//------------------------------------------------------------------------------

// Удаление p из списка; возврат приемника p
template<typename T>
Link<T>* erase(Link<T>* p)
{
    if (p == nullptr) return nullptr;
    if (p->succ) p->succ->prev = p->prev;
    if (p->prev) p->prev->succ = p->succ;
    return p->succ;
}

//------------------------------------------------------------------------------

// Переход на n позиций в списке;
// возврат nullptr, если это не возможно
// Положительное n - движение вперед;
// Отрицательное - назад
template<typename T>
Link<T>* advance(Link<T>* p, int n)
{
    if (p == nullptr) return nullptr;

    if (0 < n) {
        while (n--) {
            if (p->succ == nullptr) return nullptr;
            p = p->succ;
        }
    }
    else if (n < 0) {
        while (n++) {
            if (p->prev == nullptr) return nullptr;
            p = p->prev;
        }
    }
    return p;
}

//------------------------------------------------------------------------------

template<typename T>
void clear_connect(Link<T>* p)
{
    if (p == nullptr) return;
    p->prev = nullptr;
    p->succ = nullptr;
}

//------------------------------------------------------------------------------

// Извлекает v из списка l; Возрат пары:
// первый - указатель на новый список
// второй - указатель на извлеченный элемент
template<typename T>
pair<Link<T>*, Link<T>*> extract(Link<T>* l, const T& v)
{
    if (l == nullptr)
        return make_pair(nullptr, nullptr);

    Link<T>* p{find(l, v)};
    if (p == nullptr)
        return make_pair(l, nullptr);

    if (p == l) l = p->succ;

    erase(p);
    clear_connect(p);

    return make_pair(l, p);
}

//------------------------------------------------------------------------------

template<typename T>
void print_all(Link<T>* p)
{
    cout << "{ ";
    while (p) {
        cout << p->value;
        p = p->succ;
        if (p) cout << "\n  ";
    }
    cout << " }\n";
}

//------------------------------------------------------------------------------

#endif // LINK_HPP

//------------------------------------------------------------------------------
