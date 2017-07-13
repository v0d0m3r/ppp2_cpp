//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

string cat_dot(const string& s1, const string& s2)
{
    return s1 + '.' + s2;
}

//------------------------------------------------------------------------------

string cat_dot1(const string& s1, const string& s2, char delim)
{
    return s1 + delim + s2;
}

//------------------------------------------------------------------------------

const char* cat_dot2(const char* s1, const char* s2)
{
    if (s1==nullptr || s2 == nullptr)
        return nullptr;

    int count{0};
    const char* ps1{s1};
    const char* ps2{s2};
    while(*ps1 || *ps2) {          // Узнаём размер строк
        (*ps1) ? ++ps1 : ++ps2;
        ++count;
    }

    char* res{new char[count+2]};  // Выделяем память под строку
    char* pres{res};

    bool did_delim{false};
    while (count+1) {              // Заполняем память строкой
        if (*s1) {
            *pres = *s1;
            ++s1;
        }
        else if (*s2) {
            if (did_delim) {
                *pres = *s2;
                ++s2;
            }
            else {
                *pres = '.';
                did_delim = true;
            }
        }
        else
            *pres = '.';
        ++pres;
        --count;
    }
    *pres = 0;                     // Добавляем нуль-терминал
    return res;
}

//------------------------------------------------------------------------------

const char* cat_dot3(const char* s1, const char* s2, char delim)
{
    if (s1==nullptr || s2 == nullptr)
        return nullptr;

    int count{0};
    const char* ps1{s1};
    const char* ps2{s2};
    while(*ps1 || *ps2) {          // Узнаём размер строк
        (*ps1) ? ++ps1 : ++ps2;
        ++count;
    }

    constexpr int delta_sz = 2;    // Приращение для делиметра и нуль-символа
    // Выделяем память под результат
    char* res{new char[count+delta_sz]};
    char* pres{res};

    bool did_delim{false};
    while (count+1) {              // Заполняем память данными
        if (*s1) {                 // Заполняем строкой s1
            *pres = *s1;
            ++s1;
        }
        else if (*s2) {
            if (did_delim) {       // Если делиметр добавлен,
                                   // то заполняем строкой s2
                *pres = *s2;
                ++s2;
            }
            else {
                *pres = delim;
                did_delim = true;
            }
        }
        else                       // Для пустых строк -
            *pres = delim;         // заполняем делиметром
        ++pres;
        --count;
    }
    *pres = 0;                     // Добавляем нуль-терминал
    return res;
}

//------------------------------------------------------------------------------

void usage_cat_dog()
{
    string s1 = "Nels";
    string s2 = "Bor";
    char delim = '.';
    const char* res = cat_dot3(s1.c_str(), s2.c_str(), delim);
    cout << "cat_dot3: " << res  << '\n';
    cout << "cat_dot1: " << cat_dot1(s1, s2, delim) << '\n';
    delete[] res;
}

//------------------------------------------------------------------------------

int main()
try
{
    usage_cat_dog();
    return 0;
}
catch(exception& e) {
    cout << "error: " << e.what() << '\n';
}

//------------------------------------------------------------------------------
