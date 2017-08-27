//------------------------------------------------------------------------------

#ifndef EXERCISES_HPP
#define EXERCISES_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

struct Bad_size : runtime_error {
    Bad_size() : runtime_error("Size error") {}
};

//------------------------------------------------------------------------------s

struct Bad_sum : runtime_error {
    Bad_sum() : runtime_error("Sum error") {}
};

//------------------------------------------------------------------------------
// Exercise 19_1
template<typename T>
void f(vector<T>& v1, const vector<T>& v2)
{
    if (v1.size() != v2.size()) throw Bad_size();
    for (size_t i=0; i < v1.size(); ++i)
        v1[i] += v2[i];
}

//------------------------------------------------------------------------------
// Exercise 19_1
template<typename T>
void test_f(vector<T>& v1, const vector<T>& v2)
{
    vector<int> sum{v1};
    f(sum, v2);

    for (size_t i=0; i < v1.size(); ++i)
        if (sum[i] != v1[i]+v2[i]) throw Bad_sum();
}

//------------------------------------------------------------------------------

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    for (size_t i=0; i < v.size(); ++i) {
        os << v[i];
        (i == v.size()-1) ? os << ';' : os << ',';
    }
    return os;
}

//------------------------------------------------------------------------------
// Exercise 19_2
template<typename T, typename U, typename RT = T>
vector<RT> fprod(const vector<T>& vt, const vector<U>& vu)
{
    if (vt.size() != vu.size()) throw Bad_size();

    vector<RT> vrt;
    for (size_t i=0; i < vt.size(); ++i)
        vrt.push_back(vt[i]*vu[i]);

    return vrt;
}

//------------------------------------------------------------------------------

#endif // EXERCISES_HPP

//------------------------------------------------------------------------------
