//------------------------------------------------------------------------------

#include "Link_first.hpp"

//------------------------------------------------------------------------------

Link_first* insert(Link_first *p, Link_first *n)
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

Link_first* add(Link_first* p, Link_first* n)
{

}

//------------------------------------------------------------------------------

Link_first* erase(Link_first* p)
{
    if (p == nullptr) return nullptr;
    if (p->succ) p->succ->prev = p->prev;
    if (p->prev) p->prev->succ = p->succ;
    return p->succ;
}

//------------------------------------------------------------------------------

Link_first* find(Link_first* p, const string& s)
{
    while (p) {
        if (p->value == s) return p;
        p = p->succ;
    }
    return p;
}

//------------------------------------------------------------------------------

Link_first* advance(Link_first* p, int n)
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

void print_all(Link_first *p)
{
    cout << "{ ";
    while (p) {
        cout << p->value;
        if (p->succ) cout << ", ";
        p = p->succ;
    }
    cout << " }";
}

//------------------------------------------------------------------------------
