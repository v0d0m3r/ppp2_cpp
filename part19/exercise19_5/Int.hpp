//------------------------------------------------------------------------------

#ifndef INT_HPP
#define INT_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class Int
{
public:
                                          // Конструкторы:
    Int() : i{0} {}                       // По умолчанию
    Int(const int& ii) : i{ii} {}         // С одним аргументом
    Int(const Int& a) : i{a.get()} {}     // Копирующий
                                          // Присваивание:
    Int& operator=(const Int& a) { i = a.get(); return *this;}
                                          // Доступ:
    void set(const int& ii) { i=ii; }     // Запись
    const int& get() const { return i; }  // Чтение
private:
    int i;                                // Данные
};

//------------------------------------------------------------------------------

bool operator==(const Int& a, const Int& b)
{
    return a.get() == b.get();
}

//------------------------------------------------------------------------------

inline ostream& operator<<(ostream& os, const Int& i)
{
    return os << i.get();
}

//------------------------------------------------------------------------------

inline istream& operator>>(istream& is, Int& i)
{
    int value;
    is >> value;
    if (!is) return is;

    i = Int(value);
    return is;
}

//------------------------------------------------------------------------------

inline Int operator+(const Int& a, const Int& b)
{
    return Int(a.get() + b.get());
}

//------------------------------------------------------------------------------

inline Int operator-(const Int& a, const Int& b)
{
    return Int(a.get() - b.get());
}

//------------------------------------------------------------------------------

inline Int operator*(const Int& a, const Int& b)
{
    return Int(a.get() * b.get());
}

//------------------------------------------------------------------------------

inline Int operator/(const Int& a, const Int& b)
{
    return Int(a.get() / b.get());
}

//------------------------------------------------------------------------------

#endif // INT_HPP

//------------------------------------------------------------------------------
