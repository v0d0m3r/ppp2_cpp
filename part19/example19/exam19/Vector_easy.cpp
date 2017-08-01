//------------------------------------------------------------------------------

#include "Vector_easy.hpp"

//------------------------------------------------------------------------------

Vector_easy::Vector_easy(int s)
    : sz{s},
    elem{new double[s]}, // Инициализация члена elem
    space{s}
{
    for (int i=0; i < s; ++i) // Инициализация элементов
        elem[i] = 0;
}

//------------------------------------------------------------------------------

Vector_easy::Vector_easy(initializer_list<double> lst)
    : sz{static_cast<int>(lst.size())},
    elem{new double[sz]}, // Инициализация члена elem
    space{sz}
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
// Похож на конструктор копирования,
// но мы должны разобраться со старыми элементамиы
{
    if (this == &a) return *this;     // Самоприсваивание, ничего не делаем
    if (a.sz <= space) {              // Памяти достаточно, новая не нужна
        copy(a.elem, a.elem+sz, p);   // Копируем элементы
        sz = a.sz;
        return *this;                 // Возврат ссылки на себя
    }

    double* p{new double[a.size()]};  // Выделение памяти
    copy(a.elem, a.elem+sz, p);       // Копирование элементов
    delete[] elem;                    // Освобождение памяти
    space = sz = a.sz;                // Устанавливаем новый размер
    elem = p;                         // Переназначение указателя
    return *this;                     // Возврат ссылки на себя
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

void Vector_easy::reserve(int newalloc)
{
    if (newalloc <= space) return;   // Размер никогда не уменьшается
    double* p{new double[newalloc]}; // Выделение новой памяти
    for (int i=0; i < sz; ++i)
        p[i] = elem[i];              // Копируем старые элементы
    delete[] elem;                   // Освобождение старой памяти
    elem = p;
    space = newalloc;
}

//------------------------------------------------------------------------------

void Vector_easy::resize(int newsize)
// Создаем вектор, содержащий newsize элементов
// Инициализируем каждый элемент значением по умолчанию 0.0
// Размер никогда не уменьшается
{
    reserve(newsize);
    for (int i=sz; i < newsize; ++i)
        elem[i] = 0;    // Инициализируем новые элементы
    sz = newsize;
}

//------------------------------------------------------------------------------

void Vector_easy::push_back(double d)
// Увеличивает размер вектора на единицу;
// инициализирует новый элемент значением d
{
    if (space == 0)
        reserve(8);
    else if (sz == space)
        reserve(2*space);
    elem[sz] = d;
    ++sz;
}

//------------------------------------------------------------------------------
