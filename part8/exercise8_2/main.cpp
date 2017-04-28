//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

void print(const vector<int>& integer, string result)
{
    for (int i : integer) cout << result << i << '\n';
}

//------------------------------------------------------------------------------

void init(vector<int>& integer)
{
    for (size_t i=0; i < integer.size(); ++i)  integer[i]=i;
}

//------------------------------------------------------------------------------

void exercise8_2()
{
    vector<int> integer(10);
    init(integer);
    print(integer,"=");
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise8_2();
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
