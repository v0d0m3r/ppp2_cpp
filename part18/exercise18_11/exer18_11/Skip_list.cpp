//------------------------------------------------------------------------------

#include "Skip_list.hpp"

//------------------------------------------------------------------------------

Skip_list::Skip_list(int mm, int kk, const string& vv)
    : m{mm}, head{new Link(m)}
{
    if (kk) insert(kk, vv);
}

//------------------------------------------------------------------------------

Skip_list::Skip_list(initializer_list<string> lst)
{
    int first{0};
    for (const auto& s : lst) {
        insert(first, s);
        ++first;
    }
}

//------------------------------------------------------------------------------

Skip_list::~Skip_list()
{
    Link* p{nullptr};
    while (true) {
        p = head;
        while (p && p->next(0) && p->next(0)->next(0))
            p = p->next(0);

        if (p && p->next(0)) {
            delete p->next(0);
            p->set_next(0, nullptr);
        }
        if (p == head) {
            delete head;
            break;
        }
    }
}

//------------------------------------------------------------------------------

const string& Skip_list::find(int key) const
{
    Link* p{head};
    for (int i=l-1; 0 <= i; --i)
        while (   p->next(i)
               && p->next(i)->key() < key)
            p = p->next(i);          // Перематываем по уровню
    p = p->next(0);
    if (p && p->key() == key) return p->value;
    return empty_value();
}

//------------------------------------------------------------------------------

void Skip_list::insert(int key, const string& val)
{
    Link update{m};     // Список указателей
                        // на предшественников n
    Link* p{head};
    for (int i=l-1; 0 <= i; --i) {
        while (   p->next(i)
               && p->next(i)->key() < key)
            p = p->next(i);          // Перематываем по уровню
        update.set_next(i, p);
    }
    p = p->next(0);
    if (p && p->key() == key) {      // Ключи совпали
        p->value = val;           // Перезаписываем значение
        return;
    }

    Link* curr = new Link(random_level(m), key, val);
    if (l < curr->level()) {         // Заголовок настраиваем на элементы
        for (int i=l; i < curr->level(); ++i)
            update.set_next(i, head);
        l = curr->level();
    }

    for (int i=0; i < curr->level(); ++i) {
        curr->set_next(i, update.next(i)->next(i));
        update.next(i)->set_next(i, curr);
    }
    ++sz;
}

//------------------------------------------------------------------------------

void Skip_list::erase(int key)
{
    Link update{m};     // Список указателей
                        // на предшественников n
    Link* p{head};
    for (int i=l-1; 0 <= i; --i) {
        while (   p->next(i)
               && p->next(i)->key() < key)
            p = p->next(i);          // Перематываем по уровню
        update.set_next(i, p);
    }
    p = p->next(0);
    if (p && p->key() == key) {      // Ключи совпали
        for (int i=0; i < l; ++i) {
            if (update.next(i)->next(i) != p) break;
            update.next(i)->set_next(i, p->next(i));
        }
        delete p;
        while (l > 1 && head->next(l-1) == nullptr)
            --l;
        --sz;
    }
}

//------------------------------------------------------------------------------

string& Skip_list::operator[](int n)
{
    Link* p{head};
    for (int i=0; i <= n; ++i)
        if(p && p->next(0)) p = p->next(0);
    return p->value;
}

//------------------------------------------------------------------------------

const string& Skip_list::operator[](int n) const
{
    Link* p{head};
    for (int i=0; i <= n; ++i)
        if(p && p->next(0)) p = p->next(0);
    return p->value;
}

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Skip_list& sl)
{
    os << "{ ";
    Link* p{sl.head->next(0)};
    while (p) {
        os << p->value << "; key: " << p->key()
             << "; lev: " << p->level();
        p = p->next(0);
        if (p) cout << "\n  ";
    }
    return os << " }\n";
}

//------------------------------------------------------------------------------

const string& empty_value()
{
    static const string s{"none"};
    return s;
}

//------------------------------------------------------------------------------

int random_level(int max_lvl)
{
    int lvl{1};
    static const double prec{0.5};
    while (rand_double(0.0, 1.0)<prec && lvl<max_lvl)
        ++lvl;

    return lvl;
}

//------------------------------------------------------------------------------
