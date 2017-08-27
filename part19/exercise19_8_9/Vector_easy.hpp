//------------------------------------------------------------------------------

#ifndef VECTOR_EASY_HPP
#define VECTOR_EASY_HPP

//------------------------------------------------------------------------------

#include "Allocator.hpp"

//------------------------------------------------------------------------------

template<typename T, typename A>
struct Vector_base {
    A alloc;    // Распредилитель памяти
    T* elem;    // Начало выделенной памяти
    int sz;     // Количество элементов
    int space;  // Размер выделенной памяти

    Vector_base() : alloc{A()}, elem{nullptr}, sz{0}, space{0} {}
    Vector_base(const A& a, int size, int newaloc = 0);

    // Копирующие конструктор и присваивание
    Vector_base(const Vector_base &a) : Vector_base(a.alloc, a.sz) {}
    Vector_base& operator=(const Vector_base& a);

    // Перемещающие конструктор и присваивание
    Vector_base(Vector_base&& a);
    Vector_base& operator=(Vector_base&& a);

    ~Vector_base() { alloc.deallocate(elem, space); }
};

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector_base<T, A>::Vector_base(const A& a, int size, int newaloc)
    : alloc{a},
      elem{alloc.allocate(newaloc ? newaloc : size)},
      sz{size}, space(newaloc ? newaloc : size)
{}

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector_base<T, A>::Vector_base(Vector_base&& a)
    : Vector_base{a.alloc, a.sz, a.space} // Копируем elem и sz из a
{
    a.space = a.sz = 0;
    a.elem = nullptr;
}

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector_base<T, A>& Vector_base<T, A>::operator=(const Vector_base& a)
// Похож на конструктор копирования,
// но мы должны разобраться со старыми элементами
{
    if (this == &a) return *this;      // Самоприсваивание, ничего не делаем
    if (a.sz <= space) {               // Памяти достаточно, новая не нужна
        sz = a.sz;
        return *this;                  // Возврат ссылки на себя
    }

    T* p{alloc.allocate(a.size())};    // Выделение памяти
    alloc.deallocate(elem, space);     // Освобождение памяти

    space = sz = a.sz;                 // Устанавливаем новый размер
    elem = p;                          // Переназначение указателя
    return *this;                      // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector_base<T, A>& Vector_base<T, A>::operator=(Vector_base&& a)
{
    alloc.deallocate(elem, space);  // Освобождение памяти
    elem = a.elem;                  // Копируем elem, sz и space из a
    sz = a.sz;
    space = a.space;

    a.elem = nullptr;               // Делаем a пустым
    a.space = a.sz = 0;
    return *this;                   // Возврат ссылки на себя
}

//------------------------------------------------------------------------------

template<typename T, typename A = Allocator<T>> // Для всех типов T
class Vector_easy : private Vector_base<T, A>
{
public:
    Vector_easy() : Vector_base<T, A>() {}
    explicit Vector_easy(int s);
    Vector_easy(initializer_list<T> lst);

    // Копирующие конструктор и присваивание
    Vector_easy(const Vector_easy& a);
    Vector_easy& operator=(const Vector_easy& a);

    // Перемещающие конструктор присваивание
    //Vector_easy(Vector_easy&& a);
    //Vector_easy& operator=(Vector_easy&& a);

    ~Vector_easy(); // Деструктор

    T& at(int n);                                 // Доступ с проверкой
    const T& at(int n) const;

    T& operator[](int n) { return this->elem[n]; }      // Доступ
    const T& operator[](int n) const { return this->elem[n]; }

    int size() const { return this->sz; }               // Текущий размер
    int capacity() const { return this->space; }
                                                  // Увеличение
    void resize(int newsize, const T& def = T{});
    void push_back(const T& d);
    void reserve(int newalloc);
    void reserve1(int newalloc);
};

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector_easy<T, A>::Vector_easy(int s) : Vector_base<T, A>{A(), s}
{
    T def{T{}};
    for (int i{0}; i < s; ++i)
        uninitialized_copy(&def, &def + 1, &this->elem[i]);
}

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector_easy<T, A>::Vector_easy(initializer_list<T> lst)
    : Vector_base<T, A>{A(), static_cast<int>(lst.size())}
{
    // Инициализация элементов
    uninitialized_copy(lst.begin(), lst.end(), this->elem);
}

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector_easy<T, A>::Vector_easy(const Vector_easy<T, A>& a)
    : Vector_base<T, A>{a.Vector_base}
{
    // Инициализация элементов
    uninitialized_copy(a.elem,
                       &a.elem[a.sz], this->elem);
}

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector_easy<T, A>::~Vector_easy()
{
    for (int i{0}; i < this->sz; ++i)            // Уничтожаем созданные
        this->alloc.destroy(&this->elem[i]);
}

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector_easy<T, A>& Vector_easy<T, A>::operator=(const Vector_easy& a)
// Похож на конструктор копирования,
// но мы должны разобраться со старыми элементами
{
    if (this == &a) return *this;      // Самоприсваивание, ничего не делаем
    if (a.sz <= this->space) {         // Памяти достаточно, новая не нужна
        // Копируем элементы в инициализированную память
        copy(a.elem, &a.elem[this->sz], this->elem);

        if (a.sz > this->sz) // Копируем в неинициализированную память
            uninitialized_copy(&a.elem[this->sz], &a.elem[a.sz],
                               &this->elem[this->sz]);
        this->sz = a.sz;
        return *this;                  // Возврат ссылки на себя
    }
    // Выделение памяти
    Vector_base<T, A> b(a->alloc, a.sz);
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
T& Vector_easy<T, A>::at(int n)
{
    if (n<0 || this->sz<=n) throw Range_error(n);
    return operator[](n);
}

//------------------------------------------------------------------------------

template<typename T, typename A>
const T& Vector_easy<T, A>::at(int n) const
{
    if (n<0 || this->sz<=n) throw Range_error(n);
    return operator[](n);
}

//------------------------------------------------------------------------------

template<typename T, typename A>
void Vector_easy<T, A>::reserve(int newalloc)
{
    if (newalloc <= this->space) return;    // Размер не уменьшается
    Vector_base<T, A>
            b(this->alloc, this->sz, newalloc);       // Выделение новой памяти
    // Копируем старые элементы:
    uninitialized_copy(this->elem,
                       &this->elem[this->sz], b.elem);
    // Уничтожаем:
    for (int i=0; i < this->sz; ++i)
        this->alloc.destroy(&this->elem[i]);
    swap<Vector_base<T, A>>(*this, b); // Обмен представлений
}

//------------------------------------------------------------------------------

template<typename T, typename A>
void Vector_easy<T, A>::reserve1(int newalloc)
{
    if (newalloc <= this->space) return;    // Размер не уменьшается
    unique_ptr<T> p {this->alloc.allocate(newalloc)};
    // Копируем старые элементы:
    for (int i=0; i < this->sz; ++i)
        this->alloc.construct(&p[i], &this->elem[i]);
    // Уничтожаем:
    for (int i=0; i < this->sz; ++i)
        this->alloc.destroy(&this->elem[i]);

    this->alloc.deallocate(this->elem, this->space);
    this->elem = p.release();
    this->space = newalloc;
}

//------------------------------------------------------------------------------

template<typename T, typename A>
void Vector_easy<T, A>::resize(int newsize, const T& def)
// Создаем вектор, содержащий newsize элементов
// Инициализируем каждый элемент значением def
// Размер никогда не уменьшается
{
    reserve(newsize);
    // Создаем
    for (int i=newsize; i < this->sz; ++i)
        uninitialized_copy_n(&def, 1, &this->elem[i]);
    // Уничтожаем
    for (int i=newsize; i < this->sz; ++i)
        this->alloc.destroy(&this->elem[i]);
    this->sz = newsize;
}

//------------------------------------------------------------------------------

template<typename T, typename A>
void Vector_easy<T, A>::push_back(const T& val)
// Увеличивает размер вектора на единицу;
// инициализирует новый элемент значением d
{
    if (this->space == 0) reserve(8);     // Начинаем с 8 элементов
    else if (this->sz == this->space)
        reserve(2*this->space);           // Выделяем больше памяти

    uninitialized_copy(&val, &val+1,        // Добавляем в конец значение val
                       &this->elem[this->sz]);
    ++this->sz;                           // Увеличиваем размер
}

//------------------------------------------------------------------------------

template<typename C> void printout(const C& c)
{
    for (size_t i{0}; i < c.size(); ++i) cout << c[i] << '\n';
}

//------------------------------------------------------------------------------

template<typename T, size_t N>
void fill(array<T, N>& b, const T& val)
{
    for (size_t i{0}; i < N; ++i) b[i] = val;
}

//------------------------------------------------------------------------------

#endif // VECTOR_EASY_HPP

//------------------------------------------------------------------------------
