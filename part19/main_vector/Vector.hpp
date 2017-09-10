//------------------------------------------------------------------------------

#ifndef VECTOR_HPP
#define VECTOR_HPP

//------------------------------------------------------------------------------

#include "Vector_base.hpp"

//------------------------------------------------------------------------------

template<typename T, typename A = Allocator<T>>
class Vector : private Vector_base<T, A>
{
public:
    Vector() : Vector_base<T, A>() {}
    explicit Vector(int s);
    Vector(initializer_list<T> lst);

    // Копирующие конструктор и присваивание
    Vector(const Vector& a);
    Vector& operator=(const Vector& a);

    // Перемещающие конструктор и присваивание
    Vector(Vector&& a) : Vector_base<T, A>{move(a)} {}
    Vector& operator=(Vector&& a);

    ~Vector();                  // Деструктор
                                // Доступ с проверкой
    T& at(int n);
    const T& at(int n) const;
                                // Доступ
    T& operator[](int n) { return this->elem[n]; }
    const T& operator[](int n) const { return this->elem[n]; }

    int size() const { return this->sz; }   // Количество элементов
    int capacity() const { return this->space; }
                                            // Увеличение
    void resize(int newsize, const T& def = T{});
    void push_back(const T& e);
    void reserve(int newalloc);    
};

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector<T, A>::Vector(int s) : Vector_base<T, A>{A(), s}
{
    T def{T{}};
    for (int i{0}; i < s; ++i)
        uninitialized_copy(&def, &def + 1, &this->elem[i]);
}

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector<T, A>::Vector(initializer_list<T> lst)
    : Vector_base<T, A>{A(), static_cast<int>(lst.size())}
{
    // Инициализация элементов
    uninitialized_copy(lst.begin(), lst.end(), this->elem);
}

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector<T, A>::Vector(const Vector<T, A>& a)
    : Vector_base<T, A>{a}
{
    // Инициализация элементов
    uninitialized_copy(a.elem,
                       &a.elem[a.sz], this->elem);
}

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector<T, A>::~Vector()
{
    for (int i{0}; i < this->sz; ++i)            // Уничтожаем созданные
        this->alloc.destroy(&this->elem[i]);
}

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector<T, A>& Vector<T, A>::operator=(const Vector& a)
// Похож на конструктор копирования,
// но мы должны разобраться со старыми элементами
{
    if (this == &a) return *this;      // Самоприсваивание, ничего не делаем
    if (a.sz <= this->space) {         // Памяти достаточно, новая не нужна
        // Копируем элементы
        if (this->sz < a.sz) {
            // В инициализированной памяти
            copy(a.elem, &a.elem[this->sz], this->elem);
            // В неинициализированной памяти
            uninitialized_copy(&a.elem[this->sz], &a.elem[a.sz],
                               &this->elem[this->sz]);
        }
        else {                         // Перед копированием нужно
                                       // уничтожить лишние элементы
            for (int i{a.sz}; i < this->sz; ++i)
                this->alloc.destroy(&this->elem[i]);
            copy(a.elem, &a.elem[a.sz], this->elem);
        }
        this->sz = a.sz;
        return *this;                  // Возврат ссылки на себя
    }
    // Выделение памяти
    Vector_base<T, A> b(a.alloc, a.sz);
    uninitialized_copy(a.elem,         // Копирование элементов
                       &a.elem[a.sz], b.elem);

    // Уничтожаем старые элементы:
    for (int i{0}; i < this->sz; ++i)
        this->alloc.destroy(&this->elem[i]);

    swap<Vector_base<T, A>>(*this, b); // Обмен представлений
    return *this;                      // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector<T, A>& Vector<T, A>::operator=(Vector&& a)
{
    for (int i{0}; i < this->sz; ++i)       // Уничтожаем созданные
        this->alloc.destroy(&this->elem[i]);

    Vector_base<T, A> b{move(a)};
    swap<Vector_base<T, A>>(*this, b);      // Обмен представлений
    return *this;                           // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

template<typename T, typename A>
T& Vector<T, A>::at(int n)
{
    if (n<0 || this->sz<=n) throw Range_error(n);
    return operator[](n);
}

//------------------------------------------------------------------------------

template<typename T, typename A>
const T& Vector<T, A>::at(int n) const
{
    if (n<0 || this->sz<=n) throw Range_error(n);
    return operator[](n);
}

//------------------------------------------------------------------------------

template<typename T, typename A>
void Vector<T, A>::reserve(int newalloc)
{
    if (newalloc <= this->space) return;    // Размер не уменьшается
    Vector_base<T, A> b(this->alloc,        // Выделение новой памяти
                        this->sz, newalloc);
    uninitialized_copy(this->elem,          // Копируем старые элементы
                       &this->elem[this->sz], b.elem);
    for (int i{0}; i < this->sz; ++i)       // Уничтожаем
        this->alloc.destroy(&this->elem[i]);
    swap<Vector_base<T, A>>(*this, b);      // Обмен представлений
}

//------------------------------------------------------------------------------

template<typename T, typename A>
void Vector<T, A>::resize(int newsize, const T& def)
// Создаем вектор, содержащий newsize элементов
// Инициализируем каждый элемент значением def
// Размер никогда не уменьшается
{
    reserve(newsize);
    // Создаем
    for (int i{this->sz}; i < newsize; ++i)
        uninitialized_copy_n(&def, 1, &this->elem[i]);
    // Уничтожаем
    for (int i{newsize}; i < this->sz; ++i)
        this->alloc.destroy(&this->elem[i]);
    this->sz = newsize;
}

//------------------------------------------------------------------------------

template<typename T, typename A>
void Vector<T, A>::push_back(const T& e)
// Увеличивает размер вектора на единицу;
// инициализирует новый элемент значением e
{
    if (this->space == 0) reserve(8);   // Начинаем с 8 элементов
    else if (this->sz == this->space)
        reserve(2*this->space);         // Выделяем больше памяти

    uninitialized_copy_n(&e, 1,         // Добавляем в конец значение val
                       &this->elem[this->sz]);
    ++this->sz;                         // Увеличиваем размер
}

//------------------------------------------------------------------------------

#endif // VECTOR_HPP

//------------------------------------------------------------------------------
