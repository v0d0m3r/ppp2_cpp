/*#include "Link.hpp"

//------------------------------------------------------------------------------

Link* Link::insert(Link *n)
{
    if (n == nullptr) return this;
    if (this == nullptr) return n;

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

}

//------------------------------------------------------------------------------

Link* Link::erase()
{

}

//------------------------------------------------------------------------------

Link* Link::find(const string& s)
{

}

//------------------------------------------------------------------------------

Link* Link::advance(int n)
{

}

//------------------------------------------------------------------------------

void print_all(Link *p)
{
    cout << "{ ";
    while (p) {
        cout << p->value;
        if (p = p->next()) cout << ", ";
    }
    cout << " }";
}

//------------------------------------------------------------------------------*/
