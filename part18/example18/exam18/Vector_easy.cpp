//------------------------------------------------------------------------------

#include "Vector_easy.hpp"

//------------------------------------------------------------------------------

Vector_easy::Vector_easy(int s)
    : sz{s},
    elem{new double[s]} // Инициализация члена elem
{

    for (int i=0; i < s; ++i) // Инициализация элементов
        elem[i] = 0;
}

//------------------------------------------------------------------------------

Vector_easy::Vector_easy(initializer_list<double> lst)
    : sz{static_cast<int>(lst.size())},
    elem{new double[sz]} // Инициализация члена elem
{
    copy(lst.begin(), lst.end(), elem); // Инициализация элементов
}

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
    : sz{a.sz}, elem{a.elem}    // Копируем elem и sz из a
{
    a.sz = 0;
    a.elem = nullptr;
}

//------------------------------------------------------------------------------

Vector_easy& Vector_easy::operator=(const Vector_easy& a)
{
    double* p = new double[a.size()];   // Выделение памяти
    copy(a.elem, a.elem+sz, p);         // Копирование элементов
    delete[] elem;                      // Освобождение памяти
    elem = p;                           // Переназначение указателя
    sz = a.sz;
    return *this;                       // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

Vector_easy& Vector_easy::operator=(Vector_easy&& a)
{
    delete[] elem;                      // Освобождение памяти
    elem = a.elem;                      // Копируем elem и sz из a
    sz = a.sz;
    a.elem = nullptr;                   // Делаем a пустым
    a.sz = 0;
    return *this;                       // Возврат ссылки на себя
}

//------------------------------------------------------------------------------
