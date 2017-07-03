//------------------------------------------------------------------------------

#include "Link.hpp"

//------------------------------------------------------------------------------

Link* Link::insert(List* h, Link *n)
{
    if (n == nullptr) return this;

    n->succ = this;             // this сдедует за n

    if (h) {
        if (h->head == nullptr) h->head = this;
        if (h->head == this) {  // this - первый элемент списка
            h->head = n;        // n становится первым элементом
            return n;
        }
        Link* p{h->head};
        while (p) {             // Поиск предшественника this
            if (p->succ == this) {
                p->succ = n;    // n становится последующим
                                // предшественника this
                break;
            }
            p = p->succ;
        }
    }
    return n;
}

//------------------------------------------------------------------------------

Link* Link::add(List* h, Link* n)
{
    /*if (n==nullptr) return nullptr;

    n->succ = succ;      // Последующий this следует за n
    if (succ)            // Предшественником последующего this
        succ->prev = n;  // становится n

    n->prev = this;      // this становится
                         // предшественником n
    succ = n;            // n становится последующим this
    return n;*/
}

//------------------------------------------------------------------------------

Link* Link::erase(List* h)
{   
    /*if (succ) succ->prev = prev;
    if (prev) prev->succ = succ;
    return succ;*/
}

//------------------------------------------------------------------------------

Link* Link::find(List* h, const string& s)
{
    /*Link* p{this};
    while (p) {
        if (p->value == s) return p;
        p = p->succ;
    }
    return p;*/
}

//------------------------------------------------------------------------------

const Link* Link::find(List* h, const string& s) const
{
    const Link* p{this};
    while (p) {
        if (p->value == s) return p;
        p = p->succ;
    }
    return p;
}

//------------------------------------------------------------------------------

Link* Link::advance(List* h, int n) const
{    
    /* Link* p{this};
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
    return const_cast<Link*>(p);*/
}

//------------------------------------------------------------------------------

void print_all(Link* p)
{    
    if (p == nullptr) return;
    cout << "{ ";
    while (p) {
        cout << p->value;
        p = p->next();
        if (p) cout << ", ";
    }
    cout << " }\n";
}

//------------------------------------------------------------------------------
