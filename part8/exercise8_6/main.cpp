//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

void print(const vector<string>& str)
{
    for (size_t i=0; i < str.size(); ++i)
        if(i < str.size()-1)
            cout << str[i] << ',';
        else
            cout << str[i] << '\n';
}

//------------------------------------------------------------------------------

void init(vector<string>& str)
{
    // Размер массива не более x = 128-33, иначе будет
    // потеря данных (сужающее преобразование)
    const int begin_ascii = 33;
    for (size_t i=0; i<str.size(); ++i)  str[i]+=char(i+begin_ascii);
}

//------------------------------------------------------------------------------

void inverse1(const vector<string>& v)
{
    vector<string> v2;
    for (int i=v.size()-1; i >= 0; --i) {
        v2.push_back(v[i]);
    }
    print(v2);
}

//------------------------------------------------------------------------------

void inverse2(vector<string>& v)
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
    vector<string> v(11);
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
