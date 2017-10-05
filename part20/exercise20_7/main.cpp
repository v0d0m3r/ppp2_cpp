//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

// Возвращает итератор, указывающий на максимальный
// элемент диапазона [first, last)
template<typename Iter>
// Требует Input_iterator<Iter>
Iter high_20_4(Iter first, Iter last)
{
    Iter high{first};
    for (Iter p{first}; p != last; ++p)
        if (*high < *p) high = p;
    return high;
}

//------------------------------------------------------------------------------

void exercise20_7()
{
    vector<string> vs;
    for (string s; cin >> s;) vs.push_back(s);

    auto p{high_20_4(vs.begin(), vs.end())};
    if (p != vs.end())
        cout << "last string: " << *p << '\n';
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise20_7();
    return 0;
}
catch(const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "oops!";
    return -2;
}

//------------------------------------------------------------------------------
