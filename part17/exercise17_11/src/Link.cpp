//------------------------------------------------------------------------------

#include "Link.hpp"

//------------------------------------------------------------------------------

Link* Link::insert(Link *n)
{
    if (n==nullptr || this==nullptr) return nullptr;

    n->succ = this;      // this сдедует за n
    if (prev)            // n следует после
        prev->succ = n;  // предшественника this

    n->prev = prev;      // Предшественник this становится
                         // предшественником n
    prev = n;            // n становится предшественником this
    return n;
}

//------------------------------------------------------------------------------

Link* Link::add(Link* n)
{
    if (n==nullptr || this==nullptr) return nullptr;

    n->succ = succ;      // Последующий this следует за n
    if (succ)            // Предшественником последующего this
        succ->prev = n;  // становится n

    n->prev = this;      // this становится
                         // предшественником n
    succ = n;            // n становится последующим this
    return n;
}

//------------------------------------------------------------------------------

Link* Link::erase()
{
    if (this == nullptr) return nullptr;
    if (succ) succ->prev = prev;
    if (prev) prev->succ = succ;
    return succ;
}

//------------------------------------------------------------------------------

Link* Link::find(const string& s)
{
    Link* p{this};
    while (p) {
        if (p->value == s) return p;
        p = p->succ;
    }
    return p;
}

//------------------------------------------------------------------------------

const Link* Link::find(const string& s) const
{
    const Link* p{this};
    while (p) {
        if (p->value == s) return p;
        p = p->succ;
    }
    return p;
}

//------------------------------------------------------------------------------

Link* Link::advance(int n) const
{
    if (this == nullptr) return nullptr;

    const Link* p{this};
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
    return const_cast<Link*>(p);
}

//------------------------------------------------------------------------------

void print_all(Link* p)
{
    cout << "{ ";
    while (p) {
        cout << p->value;
        p = p->next();
        if (p) cout << ", ";
    }
    cout << " }\n";
}

//------------------------------------------------------------------------------
