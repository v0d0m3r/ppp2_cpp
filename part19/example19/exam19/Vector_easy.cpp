//------------------------------------------------------------------------------

#include "Vector_easy.hpp"

//------------------------------------------------------------------------------

Vector_easy::Vector_easy(const Vector_easy& a)
    : sz{a.size()},
    elem{new double[sz]} // Инициализация члена elem
{
    // Инициализация элементов
    copy(a.elem, a.elem+sz, elem);
}

//------------------------------------------------------------------------------

Vector_easy::Vector_easy(Vector_easy&& a)
    : sz{a.sz}, elem{a.elem}, space{sz}    // Копируем elem и sz из a
{
    a.space = a.sz = 0;
    a.elem = nullptr;
}

//------------------------------------------------------------------------------

Vector_easy& Vector_easy::operator=(const Vector_easy& a)
// Похож на конструктор копирования,
// но мы должны разобраться со старыми элементами
{
    if (this == &a) return *this;      // Самоприсваивание, ничего не делаем
    if (a.sz <= space) {               // Памяти достаточно, новая не нужна
        copy(a.elem, a.elem+sz, elem); // Копируем элементы
        sz = a.sz;
        return *this;                  // Возврат ссылки на себя
    }

    double* p{new double[a.size()]};   // Выделение памяти
    copy(a.elem, a.elem+sz, p);        // Копирование элементов
    delete[] elem;                     // Освобождение памяти
    space = sz = a.sz;                 // Устанавливаем новый размер
    elem = p;                          // Переназначение указателя
    return *this;                      // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

Vector_easy& Vector_easy::operator=(Vector_easy&& a)
{
    delete[] elem;                      // Освобождение памяти
    elem = a.elem;                      // Копируем elem и sz из a
    space = sz = a.sz;
    a.elem = nullptr;                   // Делаем a пустым
    a.space = a.sz = 0;
    return *this;                       // Возврат ссылки на себя
}

//------------------------------------------------------------------------------
