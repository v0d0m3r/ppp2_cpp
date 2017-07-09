#ifndef TEST_X_HPP
#define TEST_X_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

struct X    // Простой тестовый класс
{
    int val;

    void out(const string& s, int nv)
    {
        cerr << this << "->" << s << ": " << val
             << " (" << nv << ")\n";
    }
    X() { out("X()", 0); val = 0; }  // Конструктор по умолчанию
    X(int v) { val = v; out("X(int)", v); }
                                    // Копирующий конструктор:
    X(const X& x) { val = x.val; out("X(X&)", val);}
    X& operator=(const X& a)        // Копирующее присваивание
    {
        out("X::opertaor=()", a.val);
        val = a.val; return *this;
    }
    ~X() { out("~X()", 0); }
};

//------------------------------------------------------------------------------

#endif // TEST_X_HPP
