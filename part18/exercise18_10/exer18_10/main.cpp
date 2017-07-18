//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------
// Чтение произвольного слова с проверкой на длину
char* read_word(istream& is, int max)
{
    int n{0};
    char* buffer{new char[n+2]{0, 0}};
    for (char ch; is >> ch;) {
        if (n == max) {
            delete[] buffer;
            error("Слишком длинная строка!");
        }
        if (n == 0) buffer[n] = ch;
        else {
            char* pb = new char[n+2];
            copy(buffer, buffer+n, pb);
            delete[] buffer;

            pb[n] = ch;
            pb[n+1] = 0;
            buffer = pb;
        }
        ++n;

        if (is.get(ch)) {
            is.putback(ch);
            if (isspace(ch)) break;
        }
    }
    return buffer;
}

//------------------------------------------------------------------------------
// Чтение произвольного слова, опасно переполнением памяти
char* read_word(istream& is)
{
    int n{0};
    char* buffer{new char[n+2]{0, 0}};
    for (char ch; is >> ch;) {
        if (n == 0) buffer[n] = ch;
        else {
            char* pb = new char[n+2];
            copy(buffer, buffer+n, pb);
            delete[] buffer;

            pb[n] = ch;
            pb[n+1] = 0;
            buffer = pb;
        }
        ++n;

        if (is.get(ch)) {
            is.putback(ch);
            if (isspace(ch)) break;
        }
    }
    return buffer;
}

//------------------------------------------------------------------------------

bool is_palindrome(const char* s, int n)
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

void test_is_palindrome_arr()
{
    constexpr int max = 10;
    while (true) {
        char* s = read_word(cin, max);
        if (!cin) {
            delete[] s;
            break;
        }

        cout << s << " is";
        if (!is_palindrome(s, strlen(s))) cout << " not";
        cout << " a palindrome\n";
        delete[] s;
    }
}

//------------------------------------------------------------------------------

int main()
try
{
    test_is_palindrome_arr();
    return 0;
}
catch(exception& e) {
    cout << "error: " << e.what() << '\n';
}
catch(...) {
    cerr << "Oops!";
}

//------------------------------------------------------------------------------
