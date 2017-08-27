//------------------------------------------------------------------------------

#ifndef TASK_HPP
#define TASK_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

template<typename T>
struct S {
    explicit S(T v) : val{v} {}

    T& get(); //0{ return &val; }
    const T& get() const; // const { return &val; }

    void operator=(const  T& t) { val = t; }

private:
    T val;
};

//------------------------------------------------------------------------------

template<typename T>
T& S<T>::get() { return val; }

//------------------------------------------------------------------------------

template<typename T>
const T& S<T>::get() const { return val; }

//------------------------------------------------------------------------------

template<typename T>
ostream& operator<<(ostream& os, const S<T>& s)
{
    return os << "(S.value == " << s.get() << ')';
}

//------------------------------------------------------------------------------

template<typename T>
void read_val(T& v)
{
    cin >> v;
    if (!cin) error("Bad input!");
}

//------------------------------------------------------------------------------

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    for (size_t i=0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size()-1) os << ',';
    }
    return os;
}

//------------------------------------------------------------------------------
// Формат: val1, val2, ... valN;
template<typename T>
istream& operator>>(istream& is, vector<T>& v)
{
    char ch;
    char delim = ',';
    char end = ';';
    vector<T> tmp;
    for (T val; is >> val >> ch;) {
        if (ch!=delim && ch!=end) {
            // Нарушен формат
            is.clear(ios_base::failbit);
            return is;
        }
        tmp.push_back(val);
        if (ch == end) break;
    }
    swap(v, tmp);
    return is;
}

//------------------------------------------------------------------------------

#endif // TASK_HPP

//------------------------------------------------------------------------------
