//------------------------------------------------------------------------------

#include "Link.hpp"

//------------------------------------------------------------------------------

Link* insert(Link *p, Link *n)
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

Link* add(Link* p, Link* n)
{

}

//------------------------------------------------------------------------------

Link* erase(Link* p)
{
    if (p == nullptr) return nullptr;
    if (p->succ) p->succ->prev = p->prev;
    if (p->prev) p->prev->succ = p->succ;
    return p->succ;
}

//------------------------------------------------------------------------------

Link* find(Link* p, const string& s)
{
    while (p) {
        if (p->value == s) return p;
        p = p->succ;
    }
    return p;
}

//------------------------------------------------------------------------------

Link* advance(Link* p, int n)
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
