//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

int maxv(const vector<int>& my_vec)
{
    if (my_vec.size() <= 1)
        error("maxv: ", "Слишком маленький вектор");

    int max = my_vec.front();
    for (int i : my_vec) (max > i) ? max : max = i;

    return max;
}

//------------------------------------------------------------------------------

void init(vector<int>& integer)
{
    for (size_t i=0; i<integer.size(); ++i)  integer[i]=i;
}

//------------------------------------------------------------------------------

int main()
try {
    vector<int> my_vec(500);
    init(my_vec);

    cout << "Наибольший элемент вектора = "
         << maxv(my_vec) << '\n';

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

