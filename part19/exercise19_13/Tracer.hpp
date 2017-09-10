//------------------------------------------------------------------------------

#ifndef TRACER_HPP
#define TRACER_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class Tracer
{
    string msg;
public:
    Tracer() : msg{"default_obj"}
    { cout << "constructor " << msg << '\n'; }

    explicit Tracer(const string& message) : msg{message}
    { cout << "constructor " << msg << '\n'; }

    // Копирующие конструктор и присваивание
    Tracer(const Tracer& a) : msg{a.msg}
    { cout << "copy constructor " << msg << '\n'; }

    Tracer& operator=(const Tracer& a);

    // Перемещающие конструктор и присваивание
    Tracer(Tracer&& a);
    Tracer& operator=(Tracer&& a);

    ~Tracer() { cout << "destructor " << msg << '\n'; }
};

//------------------------------------------------------------------------------

inline Tracer& Tracer::operator=(const Tracer& a)
{
    msg = a.msg;
    cout << "copy assigment " << msg << '\n';
    return *this;
}

//------------------------------------------------------------------------------

inline Tracer::Tracer(Tracer&& a) : msg{a.msg}
{
    a.msg = "";
    cout << "move constructor " << msg << '\n';
}

//------------------------------------------------------------------------------

inline Tracer& Tracer::operator=(Tracer&& a)
{
    msg = a.msg;
    a.msg = "";
    cout << "move assigment " << msg << '\n';
    return *this;
}

//------------------------------------------------------------------------------

#endif // TRACER_HPP

//------------------------------------------------------------------------------
