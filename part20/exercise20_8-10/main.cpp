//------------------------------------------------------------------------------

#include "../example20/Document.hpp"

//------------------------------------------------------------------------------

int get_count_ch(Document& d)
{
    int count{0};
    for (char ch : d)
        if (!isspace(ch)) ++count;
    return count;
}

//------------------------------------------------------------------------------

int calc_count_word(Document& d)
{
    int count{0};
    auto p{d.begin()};
    while (p != d.end()) {
        if (!isspace(*p)) {                    // Очередное слово
            while (p!=d.end() && !isspace(*p)) // Передвигаем итератор
                ++p;                           // на конец слова
            ++count;                           // Увеличиваем счетчик
                                               // слов
            if (p == d.end()) break;           // Если достигли последнее
                                               // слово, то выходим
        }
        ++p;
    }
    return count;
}

//------------------------------------------------------------------------------

int calc_count_word2(Document& d)
{
    int count{0};
    auto p{d.begin()};
    while (p != d.end()) {
        if (isalpha(*p)) {                    // Очередное слово
            while (p!=d.end() && isalpha(*p)) // Передвигаем итератор
                ++p;                          // на конец слова
            ++count;                          // Увеличиваем счетчик
                                              // слов
            if (p == d.end()) break;          // Если достигли последнее
                                              // слово, то выходим
        }
        ++p;
    }
    return count;
}

//------------------------------------------------------------------------------

bool is_whitespace(char ch, const string& white)
{
    for (char w : white)
        if (ch == w) return true;
    return false;
}

//------------------------------------------------------------------------------

int calc_count_word3(Document& d, const string& white)
{
    int count{0};
    auto p{d.begin()};
    while (p != d.end()) {
        if (!is_whitespace(*p, white)) {       // Очередное слово
            while (p!=d.end() &&
                   !is_whitespace(*p, white))  // Передвигаем итератор
                ++p;                           // на конец слова
            ++count;                           // Увеличиваем счетчик
                                               // слов
            if (p == d.end()) break;           // Если достигли последнее
                                               // слово, то выходим
        }
        ++p;
    }
    return count;
}

//------------------------------------------------------------------------------

void exercise20_8()
{
    Document d;
    cin >> d;

    cout << "\ncount characters: "
         << get_count_ch(d) << '\n';
}

//------------------------------------------------------------------------------

void exercise20_9()
{
    Document d;
    cin >> d;

    cout << "\ncount words: "
         << calc_count_word2(d) << '\n';
}

//------------------------------------------------------------------------------

void exercise20_10()
{
    Document d;
    cin >> d;
    string wh{";. "};

    cout << "\ncount words: "
         << calc_count_word3(d, wh) << '\n';
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise20_15();
    return 0;
}
catch(const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "oops!";
    return -2;
}

//------------------------------------------------------------------------------
