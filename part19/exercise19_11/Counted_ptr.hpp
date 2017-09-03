//------------------------------------------------------------------------------

#ifndef COUNTED_PTR_HPP
#define COUNTED_PTR_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

template<typename T>
void counted_ptr_manager(T* val, int* counter)
{    
    if (val==nullptr || counter==nullptr) return;
    if (*counter)                   // Если старый счетчик не пуст,
        --*counter;                 // то уменьшаем его
    else {                          // Иначе освобождаем старые ресурсы        
        delete counter;
        delete val;
    }
}

//------------------------------------------------------------------------------

template<typename T>
class Counted_ptr
{
    T* val;
    int* counter;

public:    

    explicit Counted_ptr(const T&  v)
        : val{new T{v}}, counter{new int{0}} {}

    // Копирующие конструктор и присваивание
    Counted_ptr(const Counted_ptr& a);
    Counted_ptr& operator=(const Counted_ptr& a);

    // Перемещающие конструктор и присваивание
    Counted_ptr(Counted_ptr&& a);
    Counted_ptr& operator=(Counted_ptr&& a);

    ~Counted_ptr(); // Деструктор

    T* operator->() const { return val; }

    T& operator*() const { return *val; }

    int count() const { return *counter; }
};

//------------------------------------------------------------------------------

template<typename T>
Counted_ptr<T>::Counted_ptr(const Counted_ptr& a)
    : val{a.val}, counter{a.counter}
{
    ++*counter;
}

//------------------------------------------------------------------------------

template<typename T>
Counted_ptr<T>::Counted_ptr(Counted_ptr&& a)
    : val{a.val}, counter{a.counter}
{
    a.val = nullptr;
    a.counter = nullptr;
}

//------------------------------------------------------------------------------

template<typename T>
Counted_ptr<T>::~Counted_ptr()
{
    counted_ptr_manager(val, counter);
}

//------------------------------------------------------------------------------

template<typename T>
Counted_ptr<T>& Counted_ptr<T>::operator=(const Counted_ptr& a)
{
    if (this == &a) return *this;   // Самоприсваивание, ничего не делаем

    counted_ptr_manager(val, counter);

    counter = a.counter;            // Устанавливаем новый счетчик
    val = a.val;                    // Устанавливаем новый указатель на Т
    ++*counter;                     // Увеличиваем счетчик

    return *this;
}

//------------------------------------------------------------------------------

template<typename T>
Counted_ptr<T>& Counted_ptr<T>::operator=(Counted_ptr&& a)
{
    counted_ptr_manager(val, counter);

    counter = a.counter;            // Устанавливаем новый счетчик
    val = a.val;                    // Устанавливаем новый указатель на Т

    a.counter = nullptr;
    a.val = nullptr;

    return *this;
}

//------------------------------------------------------------------------------

#endif // COUNTED_PTR_HPP

//------------------------------------------------------------------------------
