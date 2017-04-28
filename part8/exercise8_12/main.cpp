//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

int maxv(const vector<int>& my_vec)
{
    if (my_vec.size() <= 1)
        error("maxv: ", "Слишком маленький вектор");
    int max = my_vec.front();
    for (size_t i=1; i < my_vec.size(); ++i)
        (max > my_vec[i]) ? max : max = my_vec[i];

    return max;
}

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

void get_str_size(const vector<string>& str, vector<int>& value)
{   
    for (size_t i=0; i < str.size(); ++i)
        value.push_back(str[i].size());
}

//------------------------------------------------------------------------------

void init(vector<string>& str)
{
    // Размер массива не более x = 128-33, иначе будет
    // потеря данных (сужающее преобразование)
    const int begin_ascii = 33;
    int counter = begin_ascii;
    for (size_t i=0; i < str.size(); ++i)  {
        for (size_t j = i; j < str.size(); ++j)
        {
            str[i] = str[i] + char(counter)
                    + char(counter+1);
            (counter > 118)
                    ? counter = begin_ascii
                    : counter+=2;
        }
    }
}

//------------------------------------------------------------------------------

void result()
{
    unsigned int start_time =  clock();
    vector<string> my_vec(1000);
    init(my_vec);

    vector<int> str_size;
    get_str_size(my_vec, str_size);

    print(str_size);

    cout << "Наибольший элемент вектора = "
         << maxv(str_size) << '\n';
    unsigned int end_time = clock(); // конечное время

    cout << "Время выполнения: "
         << end_time - start_time << " ms\n";
}

//------------------------------------------------------------------------------

int main()
{
    result();
    keep_window_open("~~");
    return 0;
}

//------------------------------------------------------------------------------

