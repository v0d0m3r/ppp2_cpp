//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------
// exercise 18_1
char* mstrdup(const char* s)
{
    if (s == nullptr) return nullptr;

    int count{0};
    const char* ps = s;
    while(*ps) { ++count; ++ps; }   // Узнаём размер строки
    ps = s;

    char* res = new char[count+1];  // Выделяем память под строку
    char* pres = res;

    while (s+count != ps) {         // Заполняем память строкой
        *pres = *ps;
        ++pres;
        ++ps;
    }
    *pres = 0;                      // Добавляем нуль-терминал
    return res;
}

//------------------------------------------------------------------------------
// exercise 18_4
char* mstrdup(const char* s, int n)
{
    if (s == nullptr) return nullptr;

    int count{0};
    const char* ps = s;
    while(count < n && *ps) { ++count; ++ps; }   // Узнаём размер строки
    ps = s;

    char* res = new char[count+1];  // Выделяем память под строку
    char* pres = res;

    while (s+count != ps) {         // Заполняем память строкой
        *pres = *ps;
        ++pres;
        ++ps;
    }
    *pres = 0;                      // Добавляем нуль-терминал
    return res;
}

//------------------------------------------------------------------------------

void usage_mstrdup()
{
    const char* s = "Hello, world";
    char* ns = mstrdup(s);
    cout << ns << '\n';

    delete[] ns;
}

//------------------------------------------------------------------------------
// exercise 18_2
const char* findx(const char* s, const char* x)
{
    if (s==nullptr || x==nullptr) return nullptr;
    if (*x == 0) return s;
    while (*s) {
        if (*s == *x) {
            bool is_find{true};
            const char* ps = s;
            for (const char* px = x; *px; ++px) {
                if (*ps == 0)           // Кончилась s (s < x)
                    return nullptr;
                if (*ps != *px) {       // x не входит в эту часть s
                    is_find = false;
                    break;              // Ищем дальше
                }
                ++ps;
            }
            if (is_find) break;         // Нашли вхождение
        }
        ++s;
    }
    return (*s) ? s : nullptr;
}

//------------------------------------------------------------------------------
// exercise 18_4
const char* findx(const char* s, const char* x, int ns, int nx)
{
    if (s==nullptr || x==nullptr) return nullptr;
    if (*x == 0) return s;
    int count_s{0};
    while (count_s < ns && *s) {
        if (*s == *x) {
            bool is_find{true};
            const char* ps = s;
            int count_x{0};
            for (const char* px = x; count_x<nx && *px; ++px) {
                if (*ps == 0)           // Кончилась s (s < x)
                    return nullptr;
                if (*ps != *px) {       // x не входит в эту часть s
                    is_find = false;
                    break;              // Ищем дальше
                }
                ++ps;
                ++count_x;
            }
            if (is_find) break;         // Нашли вхождение
        }
        ++s;
        ++count_s;
    }
    if (count_s == ns) return nullptr;
    return (*s) ? s : nullptr;
}

//------------------------------------------------------------------------------

void usage_findx()
{
    const char* s = "Hello my litle_friend, Sss!";
    const char* x = "my";

    const char* ps = mstrdup(s);
    const char* px = mstrdup(x);

    const char* dest = findx(ps, px);
    if (dest) cout << "findx:  " << dest << '\n';

    dest = strstr(ps, px);
    if (dest) cout << "strstr: " << dest << '\n';

    delete[] ps;
    delete[] px;
}

//------------------------------------------------------------------------------
// exercise 18_3
int mstrcmp(const char* s1, const char* s2)
{
    constexpr int big = 1;
    constexpr int small = -1;
    if (s1==nullptr && s2==nullptr) return 0;
    if (s1==nullptr) return small;
    if (s2==nullptr) return big;

    while(*s1 && *s2) {
        if (*s1 != *s2)
            return (*s1 > *s2) ? big : small;
        ++s1;
        ++s2;
    }
    if (*s1) return big;
    if (*s2) return small;
    return 0;
}

//------------------------------------------------------------------------------
// exercise 18_4
int mstrcmp(const char* s1, const char* s2, int n)
{
    constexpr int big = 1;
    constexpr int small = -1;
    if (s1==nullptr && s2==nullptr) return 0;
    if (s1==nullptr) return small;
    if (s2==nullptr) return big;

    int counter = 0;
    while(counter<n && *s1 && *s2) {
        if (*s1 != *s2)
            return (*s1 > *s2) ? big : small;
        ++s1;
        ++s2;
        ++counter;
    }
    if (counter == n) { return 0; }
    if (*s1) return big;
    if (*s2) return small;
    return 0;
}

//------------------------------------------------------------------------------

void usage_mstrcmp()
{
    const char* s1 = "Hello my z";
    const char* s2 = "Hello my litle_friend, Sss!";

    const char* ps1 = mstrdup(s1);
    const char* ps2 = mstrdup(s2);

    cout << "mstrcmp: " << mstrcmp(ps1, ps2) << '\n';

    cout << "strcmp: " << strcmp(ps1, ps2) << '\n';

    delete[] ps1;
    delete[] ps2;
}

//------------------------------------------------------------------------------
// exercise 18_4
void bad_usage_mstrdup()
{
    constexpr int n = 4;
    char ca[n];
    for (int i=0; i < n; ++i)
        ca[i] = 'A' + i;

    char* ns = mstrdup(ca);
    cout << ns << '\n';

    delete[] ns;
}

//------------------------------------------------------------------------------
// exercise 18_4
void bad_usage_mstrdup1()
{
    constexpr int n = 4;
    char ca[n];
    for (int i=0; i < n; ++i)
        ca[i] = 'A' + i;

    char* ns = mstrdup(ca, n);
    cout << ns << '\n';

    delete[] ns;
}

//------------------------------------------------------------------------------
// exercise 18_4
void bad_usage_findx()
{
    char s[] = { 'H','e', 'l', 'l', 'o', ' ', 'm', 'y', ' ', 'l', 'i', 't', 'l',
                 'e', '_', 'f', 'r', 'i', 'e', 'n', 'd', ',', ' ', 'S', 's', 's', '!'};
    char x[] = {'m', 'y'};

    const char* dest = findx(s, x);
    if (dest) cout << "findx:  " << dest << '\n';

    dest = strstr(s, x);
    if (dest) cout << "strstr: " << dest << '\n';
}

//------------------------------------------------------------------------------
// exercise 18_4
void bad_usage_findx1()
{
    char s[] = { 'H','e', 'l', 'l', 'o', ' ', 'm', 'y', ' ', 'l', 'i', 't', 'l',
                 'e', '_', 'f', 'r', 'i', 'e', 'n', 'd', ',', ' ', 'S', 's', 's', '!'};
    char x[] = {'m', 'y'};

    const char* dest = findx(s, x, sizeof(s), sizeof(x));
    if (dest) cout << "findx:  " << dest << '\n';

    //dest = strstr(s, x);
    //if (dest) cout << "strstr: " << dest << '\n';
}

//------------------------------------------------------------------------------
// exercise 18_4
void bad_usage_mstrcmp()
{
    constexpr int n = 4;
    char* s1 = new char[n];
    for (int i=0; i < n; ++i)
        s1[i] = 'A' + i;

    char* s2 = new char[n];
    for (int i=0; i < n; ++i)
        s2[i] = 'A' + i;

    cout << "mstrcmp: " << mstrcmp(s1, s2) << '\n';

    cout << "strcmp: " << strcmp(s1, s2) << '\n';

    delete[] s1;
    delete[] s2;
}

//------------------------------------------------------------------------------
// exercise 18_4
void bad_usage_mstrcmp1()
{
    constexpr int n = 4;
    char* s1 = new char[n+2];
    for (int i=0; i < n; ++i)
        s1[i] = 'A' + i;

    char* s2 = new char[n];
    for (int i=0; i < n; ++i)
        s2[i] = 'A' + i;

    cout << "mstrcmp: " << mstrcmp(s1, s2, sizeof(s2)) << '\n';

    cout << "strcmp: " << strcmp(s1, s2) << '\n';

    delete[] s1;
    delete[] s2;
}

//------------------------------------------------------------------------------
// exercise 18_4
void bad_idea()
{
    //bad_usage_mstrdup1();
    //bad_usage_findx1();
    //bad_usage_mstrcmp();
    //bad_usage_mstrcmp1();

}

//------------------------------------------------------------------------------

int main()
try
{
    bad_idea();
    return 0;
}
catch(exception& e) {
    cout << "error: " << e.what() << '\n';
}

//------------------------------------------------------------------------------
