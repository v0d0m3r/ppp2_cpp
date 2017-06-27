#ifndef LINK_FIRST_HPP
#define LINK_FIRST_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

struct Link_first {
    string value;
    Link_first* prev;
    Link_first* succ;
    Link_first(const string& v, Link_first* p = nullptr,
               Link_first* s = nullptr)
        : value{v}, prev{p}, succ{s} {}
};

//------------------------------------------------------------------------------

Link_first* insert(Link_first* p, Link_first* n); // Вставка n перед p; Возврат n
Link_first* add(Link_first* p, Link_first* n);    // Вставка n после p; Возврат n
Link_first* erase(Link_first* p);           // Удаление p из списка
                                // Возврат приемника p
Link_first* find(Link_first* p,             // Поиск s в списке;
          const string& s);     // возврат nullptr, если не найдена
Link_first* advance(Link_first* p, int n);  // Переход на n позиций в списке;
                                // возврат nullptr, если это не возможно
                                // Положительное n - движение вперед;
                                // Отрицательное - назад
void print_all(Link_first* p);

//------------------------------------------------------------------------------

#endif // LINK_FIRST_HPP
