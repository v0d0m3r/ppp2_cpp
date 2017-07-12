//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------
// Exercise 3
void to_lower(char* s)
{
    if (s == nullptr) return;

    constexpr int base = 'A' - 'a';
    for (int i=0; s[i] != '\0'; ++i)
        if ('A' <= s[i] && s[i]<='Z')
            s[i] += base;
}

//-----------------------------------------------------------------------------

void usage_tolower()
{
    char str[] = "My Dog Name!";
    char* str_array {
        new char[13] {
            'H', 'e', 'l', 'l', 'o', ' ',
            'w', 'o', 'r', 'l', 'd', '!'
        }};

    cout << "Строки до:\n" << str << '\n'
         << str_array << '\n';

    to_lower(str);
    to_lower(str_array);

    cout << "Строки после:\n" << str << '\n'
         << str_array << '\n';

    delete[] str_array;
}

//-----------------------------------------------------------------------------
// Exercise 4
char* mstrdup(const char* s)
{
    if (s == nullptr) return nullptr;

    int n = 0;
    while (s[n++] != '\0');

    char* dstr = new char[n];
    for (int i=0; i < n; ++i) dstr[i] = s[i];
    return dstr;
}

//-----------------------------------------------------------------------------

void usage_mstrdup()
{
    char* str = mstrdup("Papa!");
    cout << str << '\n';
    delete [] str;
}

//-----------------------------------------------------------------------------
// Exercise 5
const char* findx(const char* s, const char* x)
{
    if (s==nullptr || x==nullptr) return nullptr;

    constexpr char end = '\0';
    if (x == end) return s;

    const char* p = nullptr;
    for (int i=0; s[i] != end; ++i)
        if (s[i] == *x) {
            p = &s[i];
            for (int j = 1; x[j] != end; ++j) {
                if (s[i+j] == end)      // Кончилась s
                    return nullptr;
                if (s[i+j] != x[j]) {   // x не входит в эту часть s
                    p = nullptr;
                    break;              // Ищем дальше
                }
            }
            if (p) break;               // Нашли вхождение
        }
    return p;
}

//------------------------------------------------------------------------------

void usage_findx()
{
    const char* s = "Hello my litle_friend, Sss!";
    const char* x = "my";
    const char* dest = findx(s, x);
    if (dest) cout << "findx:  " << dest << '\n';

    dest = strstr(s, x);
    if (dest) cout << "strstr: " << dest << '\n';
}

//------------------------------------------------------------------------------
// Exercise 6
void memory_exhaustion()
{
    long long numbers = 0;
    for (;;) {
        char* c{new char[1000]};
        *c = 0;
        numbers += 1000;
        cout << numbers << '\n';
    }
}

//------------------------------------------------------------------------------
// Exrcise 7
void read_char_array()
{
    char ch{0};
    char* array_ch{nullptr};
    int sz{0};
    while (cin>>ch && ch!='!') {
        ++sz;
        if (array_ch == nullptr) {
            array_ch = new char(ch);
            continue;
        }
        char* tmp = new char[sz];    // Временный массив
        tmp[sz-1] = ch;
        for (int j=0; j < sz-1; ++j)
            tmp[j] = array_ch[j];

        array_ch = tmp;
    }
    if (array_ch)
        for (int i=0; i < sz; ++i)
            cout << array_ch[i] << '\n';
}

//------------------------------------------------------------------------------
// Exercise 8
void read_string()
{
    string str;
    for (char ch; cin>>ch && ch!='!';) str.push_back(ch);
    for (auto ch : str) cout << ch << '\n';
}

//------------------------------------------------------------------------------
// Exercise 9
void exercise9()
{
    int i{0};
    int* pi{&i};

    int i2{0};
    int* pi2{&i2};

    (pi2 > pi) ? cout << "Стэк растет вверх!\n":
                 cout << "Стэк растет вниз!\n";

    int* pi3{new int(0)};
    int* pi4{new int(0)};
    (pi4 > pi3) ? cout << "Адресация в куче растет вверх!\n":
                  cout << "Адресация в куче растет вниз!\n";

    delete pi3;
    delete pi4;
}

//------------------------------------------------------------------------------

int main()
try {   
    // usage_tolower();
    // usage_mstrdup();
    // usage_findx();
    // memory_exhaustion();
    // read_char_array();
    // read_string();
    exercise9();
    return 0;
}
catch(exception& e) {
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return -1;
}
catch (...) {
    cout << "Exiting\n";
    keep_window_open("~");
}

//-----------------------------------------------------------------------------
