//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

void print_until_s(const vector<string>& v, string quit)
{
    bool is_quit = false;
    for (const string& s : v) {
        if (s==quit && is_quit) return;
        if (s == quit) is_quit = true;
        cout << s << '\n';
    }
}

//------------------------------------------------------------------------------

void init(vector<string>& str)
{
    // Размер массива не более x = 128-33, иначе будет
    // потеря данных (сужающее преобразование)
    const int begin_ascii = 33;
    int counter = begin_ascii;
    for (size_t i=0; i < str.size(); ++i)  {
        str[i] = str[i] + char(counter)
                + char(counter+1);
        (counter > 118)
                ? counter = begin_ascii
                : counter+=2;
    }
}

//------------------------------------------------------------------------------

int main()
{
    vector<string> my_vec(200);
    init(my_vec);
    print_until_s(my_vec,"YZ");

    keep_window_open("~~");
    return 0;
}

//------------------------------------------------------------------------------

