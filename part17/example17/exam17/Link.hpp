#ifndef LINK_HPP
#define LINK_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

struct Link {
    string value;
    Link* prev;
    Link* succ;
    Link(const string& v, Link* p = nullptr, Link* s = nullptr)
        : value{v}, prev{p}, succ{s} {}
};

//------------------------------------------------------------------------------

Link* insert(Link* p, Link* n); // Вставка n перед p; Возврат n
Link* add(Link* p, Link* n);    // Вставка n после p; Возврат n
Link* erase(Link* p);           // Удаление p из списка
                                // Возврат приемника p
Link* find(Link* p,             // Поиск s в списке;
          const string& s);     // возврат nullptr, если не найдена
Link* advance(Link* p, int n);  // Переход на n позиций в списке;
                                // возврат nullptr, если это не возможно
                                // Положительное n - движение вперед;
                                // Отрицательное - назад

//------------------------------------------------------------------------------

#endif // LINK_HPP
