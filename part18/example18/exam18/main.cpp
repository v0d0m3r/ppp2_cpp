//------------------------------------------------------------------------------

#include "Vector_easy.hpp"
#include "Test_x.hpp"

//------------------------------------------------------------------------------

X glob(2);  //Глобальня переменная
X xcopy(X a) { return a; }
X xcopy2(X a) { X aa = a; return aa; }
X& ref_to(X& a) { return a; }
X* make(int i) { X a(i); return new X(a); }
struct XX { X a; X b; };

//------------------------------------------------------------------------------

void example18_4()
{
    X loc{4};           // Локальная переменная
    X loc2{loc};        // Копирующий конструктор

    loc = X{5};         // Копирующее присваивание
    loc2 = xcopy(loc);  // Передача по значению и возврат
    loc2 = xcopy2(loc);

    X loc3{6};
    X& r = ref_to(loc); // Передача по ссылке и возврат
    delete make(7);
    delete make(8);
    vector<X> v(4);     // Значения по умолчанию
    XX loc4;
    X* p = new X{9};    // X в динамической памяти
    delete p;
    X* pp = new X[5];   // Массив X в динамической памяти
    delete[] pp;
}

//------------------------------------------------------------------------------

int mystrlen(const char* p)
{
    int count = 0;
    while(*p) { ++count; ++p; }
    return count;
}

//------------------------------------------------------------------------------

int mystrlen1(const char a[])
{
    int count = 0;
    while(a[count]) { ++count; }
    return count;
}

//------------------------------------------------------------------------------

char lots[100000];

//------------------------------------------------------------------------------

void f()
{
    int nchar = mystrlen1(lots);
    char ac[] = "Beorn";
    cout << "sizeof(ac): " << sizeof(ac) << '\n';
    cout << "strlen(ac): " << strlen(ac) << '\n';
}

//------------------------------------------------------------------------------

bool is_palindrome(const string& s)
{
    int first{0};               // Индекс первой буквы
                                // Индекс последней буквы
    int last{static_cast<int>(s.length()) - 1};
    while (first < last) {      // Мы ещё не достигли середины слова
        if (s[first] != s[last]) return false;
        ++first;                // Переход вперед
        --last;                 // Переход назад
    }
    return true;
}

//------------------------------------------------------------------------------

void example18_7_1()
{
    for (string s; cin >> s; ) {
        cout << s << " is";
        if (!is_palindrome(s)) cout << " not";
        cout << " a palindrome\n";
    }
}

//------------------------------------------------------------------------------

istream& read_word(istream& is, char* buffer, int max)
{
    is.width(max);  // При выполнении следующего оператора >>
                    // будет считано не более max-1 символов
    is >> buffer;   // Читаем слово, завершающееся пробельным
                    // символом, добавляем в конец нулевой символ
    return is;
}

//------------------------------------------------------------------------------

bool is_palindrome(const char s[], int n)
{
    int first{0};               // Индекс первой буквы
    int last{n - 1};            // Индекс последней буквы
    while (first < last) {      // Мы ещё не достигли середины слова
        if (s[first] != s[last]) return false;
        ++first;                // Переход вперед
        --last;                 // Переход назад
    }
    return true;
}

//------------------------------------------------------------------------------

void example18_7_2()
{
    constexpr int max = 128;
    for (char s[max]; read_word(cin, s, max); ) {
        cout << s << " is";
        if (!is_palindrome(s, strlen(s))) cout << " not";
        cout << " a palindrome\n";
    }
}

//------------------------------------------------------------------------------

bool is_palindrome(const char* first, const char* last)
{
    while (first < last) {      // Мы ещё не достигли середины слова
        if (*first != *last) return false;
        ++first;                // Переход вперед
        --last;                 // Переход назад
    }
    return true;
}

//------------------------------------------------------------------------------

bool is_palindrome_recursive(const char *first, const char *last)
{
    while (first < last) {      // Мы ещё не достигли середины слова
        if (*first != *last) return false;
        return is_palindrome_recursive(first+1, last-1);
    }
    return true;
}

//------------------------------------------------------------------------------

void example18_7_3()
{
    constexpr int max = 128;
    for (char s[max]; read_word(cin, s, max); ) {
        cout << s << " is";
        if (!is_palindrome(&s[0], &s[strlen(s)-1]))
            cout << " not";
        cout << " a palindrome\n";
    }
}

//------------------------------------------------------------------------------

int main()
try
{   
    example18_7_3();
    return 0;
}
catch(exception& e) {
    cout << "error: " << e.what() << '\n';
}

//------------------------------------------------------------------------------
