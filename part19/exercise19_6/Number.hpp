//------------------------------------------------------------------------------

#ifndef NUMBER_HPP
#define NUMBER_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

template<typename T>
class Number
{
public:
                                          // Конструкторы:
    Number() : v{0} {}                       // По умолчанию
    Number(const T& vv) : v{vv} {}         // С одним аргументом
    Number(const Number& a) : v{a.get()} {}     // Копирующий
                                          // Присваивание:
    Number& operator=(const Number& a)
    { v = a.get(); return *this;}
                                          // Доступ:
    void set(const T& vv) { v=vv; }     // Запись
    const T& get() const { return v; }  // Чтение
private:
    T v;                                // Данные
};

//------------------------------------------------------------------------------

template<typename T>
bool operator==(const Number<T>& a, const Number<T>& b)
{
    return a.get() == b.get();
}

//------------------------------------------------------------------------------

template<typename T>
ostream& operator<<(ostream& os, const Number<T>& i)
{
    return os << i.get();
}

//------------------------------------------------------------------------------

template<typename T>
istream& operator>>(istream& is, Number<T>& i)
{
    T value;
    is >> value;
    if (!is) return is;

    i = Number<T>(value);
    return is;
}

//------------------------------------------------------------------------------

template<typename T>
Number<T> operator+(const Number<T>& a, const Number<T>& b)
{
    return Number<T>(a.get() + b.get());
}

//------------------------------------------------------------------------------

template<typename T, typename U>
U operator+(const Number<T>& a, const U& b)
{
    return a.get() + b;
}

//------------------------------------------------------------------------------

template<typename T, typename U>
U operator+(const U& b, const Number<T>& a)
{
    return a + b;
}

//------------------------------------------------------------------------------

template<typename T>
Number<T> operator-(const Number<T>& a, const Number<T>& b)
{
    return Number<T>(a.get() - b.get());
}

//------------------------------------------------------------------------------

template<typename T>
Number<T> operator*(const Number<T>& a, const Number<T>& b)
{
    return Number<T>(a.get() * b.get());
}

//------------------------------------------------------------------------------

template<typename T, typename U, typename RT = T>
Number<RT> operator*(const Number<T>& a, const Number<U>& b)
{
    return Number<RT>(a.get() * b.get());
}

//------------------------------------------------------------------------------

template<typename T, typename U>
U operator*(const Number<T>& a, const U& b)
{
    return a.get() * b;
}

//------------------------------------------------------------------------------

template<typename T, typename U>
U operator*(const U& b, const Number<T>& a)
{
    return a * b;
}

//------------------------------------------------------------------------------

template<typename T>
Number<T> operator/(const Number<T>& a, const Number<T>& b)
{
    return Number<T>(a.get() / b.get());
}

//------------------------------------------------------------------------------

template<typename T>
Number<T> operator%(const Number<T>& a, const Number<T>& b)
{
    return Number<T>(a.get() % b.get());
}

//------------------------------------------------------------------------------

#endif // NUMBER_HPP

//------------------------------------------------------------------------------
