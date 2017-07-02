//------------------------------------------------------------------------------

#include "Link.hpp"

//------------------------------------------------------------------------------

Link* Link::insert(Link *n)
{
    if (n==nullptr) return this;

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
    if (n==nullptr) return this;

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
    if (succ) succ->prev = prev;
    if (prev) prev->succ = succ;
    return succ;    
}

//------------------------------------------------------------------------------

Link* Link::find(const string& s)
{
    Link* p{this};
    while (p) {
        if (p->god.name == s) return p;
        p = p->succ;
    }
    return p;
}

//------------------------------------------------------------------------------

const Link* Link::find(const string& s) const
{
    const Link* p{this};
    while (p) {
        if (p->god.name == s) return p;
        p = p->succ;
    }
    return p;
}

//------------------------------------------------------------------------------

Link* Link::advance(int n) const
{
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

Link* Link::add_ordered(Link* n)
{
    if (n==nullptr) return this;
    if (n->god.name < god.name) return insert(n);

    Link* p{this};
    while (p->god.name <= n->god.name) {
        if (p->succ == nullptr) {
            p->add(n);
            return this;
        }
        p = p->succ;
    }
    p->insert(n);
    return this;
}

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const God& g)
{
    return os << '(' << g.name
              << ", " << g.myth
              << ", " << g.veh
              << ", " << g.weap << ')';
}

//------------------------------------------------------------------------------
// Извлекает s из списка l; Возрат пары:
// первый - указатель на новый список
// второй - указатель на извлеченный элемент
pair<Link*, Link*> extract(Link* l, const string& s)
{
    if (l == nullptr)
        return pair<Link*, Link*>(nullptr, nullptr);

    Link* p{l->find(s)};
    if (p == nullptr)
        return pair<Link*, Link*>(l, nullptr);

    if (p == l) l = p->next();

    p->erase();
    p->clear_connect();

    return pair<Link*, Link*>(l, p);
}

//------------------------------------------------------------------------------

void print_all(Link* p)
{
    cout << "{ ";
    while (p) {
        cout << p->god;
        p = p->next();
        if (p) cout << "\n  ";
    }
    cout << " }\n";
}

//------------------------------------------------------------------------------
