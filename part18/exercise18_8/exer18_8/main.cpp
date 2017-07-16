//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

bool is_palindrome(const string& s)
{
    string tmp;
    for (int i = s.size()-1; 0 <= i; --i)
        tmp.push_back(s[i]);
    return s == tmp;
}

//------------------------------------------------------------------------------

void test_palindrome_str()
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
    char* t = new char[n];
    int first{0};               // Индекс первой буквы
    int last{n - 1};            // Индекс последней буквы

    while (first < n) {      // Мы ещё не достигли середины слова
        t[first] = s[last];
        ++first;                // Переход вперед
        --last;                 // Переход назад
    }

    bool res{true};
    for (int i=0; i < n; ++i)
        if(t[i] != s[i]) {
            res = false;
            break;
        }
    delete[] t;
    return res;
}

//------------------------------------------------------------------------------

void test_palindrome_arr()
{
    constexpr int max = 128;
    cout << "test_palindrome_arr:\n";
    for (char s[max]; read_word(cin, s, max); ) {
        cout << s << " is";
        if (!is_palindrome(s, strlen(s))) cout << " not";
        cout << " a palindrome\n";
    }
}

//------------------------------------------------------------------------------

bool is_palindrome(const char* first, const char* last)
{
    char* tmp = new char[last-first+1];
    char* first_tmp = tmp;
    const char* l{last};
    while (first <= last) {     // Копируем строку в обратном порядке
        *first_tmp = *last;
        ++first_tmp;            // Переход вперед
        --last;                 // Переход назад
    }
    first_tmp = tmp;
    last = l;

    bool res{true};
    while (first <= last) {     // Проходим строку
        if (*first != *first_tmp) {
            res = false;
            break;
        }
        ++first;                // Переход вперед
        ++first_tmp;
    }
    delete[] tmp;
    return res;
}

//------------------------------------------------------------------------------

void test_palindrome_ptr()
{
    constexpr int max = 128;
    cout << "test_palindrome_ptr:\n";
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
    //test_palindrome_str();
    //test_palindrome_arr();
    test_palindrome_ptr();
    return 0;
}
catch(exception& e) {
    cout << "error: " << e.what() << '\n';
}

//------------------------------------------------------------------------------

