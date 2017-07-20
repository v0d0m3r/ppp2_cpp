//------------------------------------------------------------------------------

#include "Link.hpp"

//------------------------------------------------------------------------------

Skip_list::Skip_list(int mm, Link* c)
    : m{mm}, h{new Link(m)}, curr{c}
{
    if (c) {
        l = c->level();
        cnt = 1;
    }
}

//------------------------------------------------------------------------------

Link* Skip_list::insert(Link* n)
{
    if (n == nullptr) return nullptr;
    if (n->level() > m)
        error("Skip_list::insert: большой уровень узла!");
    if (cnt == 0) { // Пустой список
        l = n->level();

        for (int i=0; i < l; ++i) {
            h->set_next(i, n);
            n->set_next(i, nullptr); // Нужно ли это?
        }

        curr = n; // n становится текущим элементом списка
        ++cnt;
        return n;
    }
    Link* p{h};
    for (int i=l-1; 0 <= i; --i) {
        while (   p->next(i)
               && n->key > p->next(i)->key) // Перематываем по уровню
            p = p->next(i);
        if (i) continue;

        if (p->key == n->key) {             // Ключи совпали
            p->value = n->value;            // Перезаписываем значение
            curr = p;
            break;
        }
        if (l < n->level()) {               // Заголовок настраиваем на элементы
            for (int j=l+1; j <= n->level(); ++j)
                h->set_next(j, p);
            l = n->level();
        }
    }
    Link* frst{h};
    for (int i=0; i <= l; ++i) {
        while (frst->next(i) && frst->next(i)->key < p->key)
            frst = frst->next(i);
        n->set_next(i, frst->next(i));
        frst->set_next(i, n);
    }
    curr = frst;
    return curr;
}

//------------------------------------------------------------------------------
