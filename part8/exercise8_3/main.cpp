//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

void print(const vector<int>& integer)
{
    for (int i : integer)
        (i == integer.back()) ? cout << i << '\n'
                              : cout << i << ',';
}

//------------------------------------------------------------------------------

void fibonacci(int x, int y, vector<int>& v, int n)
{
    v.push_back(x);
    v.push_back(y);

    for (int i=2; i<n; ++i) v.push_back(v[i-1]+v[i-2]);

    print(v);
}

//------------------------------------------------------------------------------

void exercise8_3()
{
    vector<int> v;
    fibonacci(1, 2, v, 45);
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise8_3();

    keep_window_open("~~");
    return 0;
}
catch (exception& e) {
    cerr << "ошибка: " << e.what() << '\n'; // Вывод сообщения об ошибке
    keep_window_open("~~");
    return 1;
}
catch (...) {
    cerr << "Упс: неизвестное исключение!\n";
    keep_window_open("~~");
    return 2;
}

//------------------------------------------------------------------------------
