//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

void print(const vector<int>& integer)
{
    for (size_t i=0; i < integer.size(); ++i)
        if(i < integer.size()-1)
            cout << integer[i] << ',';
        else
            cout << integer[i] << '\n';
}

//------------------------------------------------------------------------------

void init(vector<int>& integer)
{
    for (size_t i=0; i<integer.size(); ++i)  integer[i]=i+2;
}

//------------------------------------------------------------------------------

void inverse1(const vector<int>& v)
{
    vector<int> v2;
    for (int i=v.size()-1; i >= 0; --i) {
        v2.push_back(v[i]);
    }
    print(v2);
}

//------------------------------------------------------------------------------

void inverse2(vector<int>& v)
{
    int j = v.size()-1;
    for (size_t i=0; i<(v.size()/2+1); ++i) {
        swap(v[i],v[j]);
        --j;
    }
    print(v);
}

//------------------------------------------------------------------------------

int main()
{
    vector<int> v(11);
    init(v);
    cout << "Начальная последовательность:";
    print(v);
    cout << "Результат1: ";
    inverse1(v);
    cout << "Результат2: ";
    inverse2(v);

    keep_window_open("~~");
    return 0;
}

//------------------------------------------------------------------------------
