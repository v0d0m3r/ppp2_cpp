//------------------------------------------------------------------------------

#ifndef VECTOR_EASY_HPP
#define VECTOR_EASY_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

template<typename T> // Для всех типов T
class Vector_easy
{
/*
    Инвариант:
        для 0<=n<sz значение elem[n] является n-м элементом
        sz<=space
        если sz<space, то после elem[sz-1] есть место
        для (space-sz) элементов типа T
*/
    allocator<T> alloc; // Работает с памятью выделяемой для элементов
    int sz;             // Размер
    T* elem;            // Указатель на элементы (или nullptr)
    int space;          // Количество элементов плюс количество
                        // свободных слотов
public:
    Vector_easy() : sz{0}, elem{nullptr}, space{0} {}
    explicit Vector_easy(int s);
    Vector_easy(initializer_list<T> lst);

    // Копирующие конструктор и присваивание
    Vector_easy(const Vector_easy& a);
    Vector_easy& operator=(const Vector_easy& a);

    // Перемещающие конструктор присваивание
    Vector_easy(Vector_easy&& a);
    Vector_easy& operator=(Vector_easy&& a);

    ~Vector_easy() { delete[] elem; }             // Деструктор

    T& at(int n);      // Доступ с проверкой
    const T& at(int n) const;

    T& operator[](int n) { return elem[n]; }      // Доступ
    const T& operator[](int n) const { return elem[n]; }

    int size() const { return sz; }               // Текущий размер
    int capacity() const { return space; }
                                                  // Увеличение
    void resize(int newsize, T def = T{});
    void push_back(const T& d);
    void reserve(int newalloc);
};

//------------------------------------------------------------------------------

template<typename T>
Vector_easy<T>::Vector_easy(int s) : sz{s}, elem{new T[s]}, space{s}
{
    for (int i=0; i < s; ++i) // Инициализация элементов
        elem[i] = T{};
}

//------------------------------------------------------------------------------

template<typename T>
Vector_easy<T>::Vector_easy(initializer_list<T> lst)
    : sz{static_cast<int>(lst.size())},
    elem{new T[sz]}, // Инициализация члена elem
    space{sz}
{
    copy(lst.begin(), lst.end(), elem); // Инициализация элементов
}

//------------------------------------------------------------------------------

template<typename T>
T& Vector_easy<T>::at(int n)
{
    if (n<0 || sz<=n) throw Range_error(n);
    return operator[](n);
}

//------------------------------------------------------------------------------

template<typename T>
const T& Vector_easy<T>::at(int n) const
{
    if (n<0 || sz<=n) throw Range_error(n);
    return operator[](n);
}

//------------------------------------------------------------------------------

template<typename T>
void Vector_easy<T>::reserve(int newalloc)
{
    if (newalloc <= space) return;   // Размер никогда не уменьшается
    T* p = alloc.allocate(newalloc); // Выделение новой памяти
    // Копируем старые элементы:
    for (int i=0; i < sz; ++i) alloc.construct(p[i], elem[i]);
    // Уничтожаем:
    for (int i=0; i < sz; ++i) alloc.destroy(elem[i]);
    alloc.deallocate(elem, space);   // Освобождение старой памяти
    elem = p;
    space = newalloc;
}

//------------------------------------------------------------------------------

template<typename T>
void Vector_easy<T>::resize(int newsize, T def)
// Создаем вектор, содержащий newsize элементов
// Инициализируем каждый элемент значением def
// Размер никогда не уменьшается
{
    reserve(newsize);
    // Создаем
    for (int i=sz; i < newsize; ++i) alloc.construct(elem[i], def);
    // Уничтожаем
    for (int i=newsize; i < sz; ++i) alloc.destroy(elem[i]);
    sz = newsize;
}

//------------------------------------------------------------------------------

template<typename T>
void Vector_easy<T>::push_back(const T& val)
// Увеличивает размер вектора на единицу;
// инициализирует новый элемент значением d
{
    if (space == 0) reserve(8);     // Начинаем с 8 элементов
    else if (sz == space)
        reserve(2*space);           // Выделяем больше памяти
    alloc.construct(elem[sz], val); // Добавляем в конец значение val
    ++sz;                           // Увеличиваем размер
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
