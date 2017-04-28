//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

int maxv(const vector<int>& my_vec)
{
    int max = my_vec.front();
    for (int i : my_vec) (max > i) ? max : max = i;

    return max;
}

//------------------------------------------------------------------------------

int minv(const vector<int>& my_vec)
{
    int min = my_vec.front();
    for (int i : my_vec) (min < i) ? min : min = i;

    return min;
}

//------------------------------------------------------------------------------

int average_v(const vector<int>& my_vec)
{
    int sum = 0;
    for (size_t i=0; i<my_vec.size(); ++i)
        sum += my_vec[i];

    return int(sum/my_vec.size());
}

//------------------------------------------------------------------------------

int median_v(const vector<int>& my_vec)
{
    vector<int> v = my_vec;
    sort(v.begin(),v.end());

    int residue = my_vec.size()%2;
    int count = my_vec.size()/2;

    return (residue == 0)
            ? static_cast<int>((v[count] + v[count+1])/2.0) // Четное
            : v[count];
}


//------------------------------------------------------------------------------

struct My_srtuct {
    int max;
    int min;
    int average;
    int median;
    My_srtuct()
        : max(0), min(0), average(0), median(0) {}
};

//------------------------------------------------------------------------------

My_srtuct result(const vector<int>& my_vec)
{
    if (my_vec.size() <= 1)
        error("result: ", "Слишком маленький вектор");
    My_srtuct ms;
    ms.max = maxv(my_vec);
    ms.min = minv(my_vec);
    ms.average = average_v(my_vec);
    ms.median = median_v(my_vec);
    return ms;
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

    My_srtuct ms;
    ms = result(my_vec);

    cout << "Наибольший элемент вектора = "
         << ms.max << '\n';

    cout << "Наименьший элемент вектора = "
         << ms.min << '\n';

    cout << "Среднее значение = "
         << ms.average << '\n';

    cout << "Медиана = "
         << ms.median << '\n';

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

