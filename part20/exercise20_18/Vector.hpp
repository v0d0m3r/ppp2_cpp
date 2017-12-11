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
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using size_type = unsigned int;

    class iterator;   // Тип-член класса: iterator
    using const_iterator = const iterator;

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

    T& front() { return *this->elem; }
    const T& front() const { return *this->elem; }
    T& back()  { return this->elem[this->sz-1]; }
    const T& back()  const { return this->elem[this->sz-1]; }
    iterator begin()
    { return iterator{this->elem, this->elem, this->elem + this->sz}; }
    const_iterator begin() const
    { return iterator{this->elem, this->elem, this->elem + this->sz}; }
    iterator end()
    { return iterator{this->elem + this->sz, this->elem, this->elem + this->sz}; }
    const_iterator end() const
    { return iterator{this->elem + this->sz, this->elem, this->elem + this->sz}; }

    size_type size() const { return this->sz; }   // Количество элементов
    int capacity() const { return this->space; }
                                                  // Увеличение
    void resize(int newsize, const T& def = T{});
    void push_front(const T& e);
    void push_back(const T& e);
    void reserve(int newalloc);
    Iterator<Vector<T, A> > insert(iterator p, const T& val);
    Iterator<Vector<T, A> > erase(iterator p);
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
class Vector<T, A>::iterator {
    pointer curr;
    pointer first;
    pointer last;
public:
    using iterator_category = random_access_iterator_tag;

    friend class Vector;
    iterator(pointer c, pointer f, pointer l);

    // Вперед:
    iterator& operator++()
    {
        if (curr == last) throw Range_error(last - curr);
        ++curr;
        return *this;
    }

    // Назад:
    iterator& operator--()
    {
        if (curr == first) throw Range_error(-1);
        --curr;
        return *this; }

    iterator& operator+=(difference_type n)
    {
        if (n >= 0) while (n--) ++(*this);
        else        while (n++) --(*this);
        return *this;
    }

    iterator& operator-=(difference_type n) { return *this += -n; }

    iterator operator+(difference_type n)
    {
        iterator temp{*this};
        return temp += n;
    }

    iterator operator-(difference_type n)
        { iterator temp{*this}; return temp -= n; }

    difference_type operator-(const iterator& rhs) const
        { return curr - rhs.curr; }

    // Разыменование (получение значения):
    reference operator*() { return *curr; }

    reference operator[](int n)
        { return *(*this + n); }
    const reference operator[](int n) const
        { return *(*this + n); }

    bool operator==(const iterator& b) const
        { return curr == b.curr; }
    bool operator!=(const iterator& b) const
        { return curr != b.curr; }
    bool operator<(const iterator& b) const
        { return b - *this > 0; }
    bool operator>(const iterator& b) const
        { return b < *this; }
    bool operator>=(const iterator& b) const
        { return !(*this < b); }
    bool operator<=(const iterator& b) const
        { return !(*this > b); }
};

//------------------------------------------------------------------------------

template<typename T, typename A>
Vector<T, A>::iterator::iterator(pointer c, pointer f, pointer l)
    : curr{c}, first{f}, last{l}
{
    if (distance(f, c)<0 || distance(c, l)<0)
        error("iterator is not located between first and last");
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

template<typename T, typename A>
void Vector<T, A>::push_front(const T& e)
// Увеличивает размер вектора на единицу;
// инициализирует новый элемент значением e
{
    insert(begin(), e);
}

//------------------------------------------------------------------------------

template<typename T, typename A>
// Требует Element<T>() и Allocator<A>()
Iterator<Vector<T, A>> Vector<T, A>::erase(iterator p)
{
    if (p == end()) return p;
    if (begin() == end()) return end();
    for (auto pos{p+1}; pos != end(); ++p)
        *(pos-1) = *p;          // Копируем элементы на
                                // одну позицию влево
    this->alloc.destroy(&*(end()-1)); // Уничтожаем лишнюю копию
                                // последнего элемента
    --this->sz;
    return p;
}

//------------------------------------------------------------------------------

template<typename T, typename A>
// Требует Element<T>() и Allocator<A>()
Iterator<Vector<T, A>> Vector<T, A>::insert(iterator p, const T& val)
{
    int index{p - begin()};
    if (size() == static_cast<size_type>(capacity()))   // Обеспечиваем
        reserve(size()==0 ? 8 : 2 * size());            // достаточное место

    // Сначала копируем последний элемент в
    // неинициализированную память:
    uninitialized_copy_n(&back(), 1, this->elem + this->sz);
    ++this->sz;
    iterator pp{begin() + index};   // Место для размещения val
    for (auto pos{end()-1}; pos != pp; --pos)
        *pos = *(pos-1);            // Копируем элементы на одну
                                    // позицию вправо
    *(begin()+index) = val;         // "Вставка" val
    return pp;
}

//------------------------------------------------------------------------------

#endif // VECTOR_HPP

//------------------------------------------------------------------------------
