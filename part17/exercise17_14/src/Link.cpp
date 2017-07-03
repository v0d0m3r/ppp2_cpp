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

Link* Link::add(Link* n)
{
    if (n==nullptr) return nullptr;

    n->succ = succ;      // Последующий this следует за n
    succ = n;            // n становится последующим this
    return n;
}

//------------------------------------------------------------------------------

Link* Link::erase(List* h)
{
    if (h==nullptr || h->head==nullptr)
        return succ;

    Link* p{h->head};
    while (p) {             // Поиск предшественника this
        if (p->succ == this) {
            p->succ = succ; // Последующий this становится
                            // последующим предшественника this
            break;
        }
        p = p->succ;
    }
    return succ;
}

//------------------------------------------------------------------------------

Link* Link::find(List* h, const string& s)
{
    if (h==nullptr) return nullptr;

    Link* p{h->head};
    while (p && p->value != s) p = p->succ;
    return p;
}

//------------------------------------------------------------------------------

const Link* Link::find(List* h, const string& s) const
{
    if (h==nullptr) return nullptr;

    const Link* p{h->head};
    while (p && p->value != s) p = p->succ;
    return p;
}

//------------------------------------------------------------------------------

Link* Link::advance(List* h, int n) const
{
    if (h == nullptr) return nullptr;

    const Link* p{nullptr};
    if (0 < n) {
        p = this;
        while (n--) {
            if (p->succ == nullptr) return nullptr;
            p = p->succ;
        }
    }
    else {
        p = h->head;
        int counter{0};
        while (p && p->succ!=this) {
            p = p->succ;
            --counter;
        }
        if (n < counter) return nullptr;

        counter -= n;
        while (counter++) p = p->succ;
    }
    return const_cast<Link*>(p);
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

void print_all(List* h)
{
    if (h==nullptr) return;
    print_all(h->head);
}

//------------------------------------------------------------------------------
