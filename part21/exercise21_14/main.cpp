//------------------------------------------------------------------------------

#include "../exercise21_13/Clear_punctstream.hpp"
#include "Finder.hpp"

//------------------------------------------------------------------------------

void word_counts(const map<string, int>& words)
{
    cout << "Введите слово, чтобы узнать "
            "сколько раз оно встречается в файле\n";
    string w;
    cin >> w;
    if (!cin) error("bad input");
    cout << w << ": " << get_word_counts(words, w) << '\n';
}

//------------------------------------------------------------------------------

void words_max_times(const map<string, int>& words)
{
    auto max_times{get_words_max_times(words)};
    cout << "max times:\n";
    for (const auto& p : max_times)
        cout << '(' << p.first << ',' << p.second << ")\n";
}

//------------------------------------------------------------------------------

void long_strs(const map<string, int>& words)
{
    if (words.begin() == words.end()) return;
    auto long_str_tb{
        get_long_str(words, Longer_than{words.begin()->first})
    };
    cout << "long str:\n";
    for (const auto& p : long_str_tb)
        cout << '(' << p.first << ',' << p.second << ")\n";
}

//------------------------------------------------------------------------------

void short_strs(const map<string, int>& words)
{
    if (words.begin() == words.end()) return;
    auto short_str_tb{
        get_long_str(words, Shorter_than{words.begin()->first})
    };
    cout << "short str:\n";
    for (const auto& p : short_str_tb)
        cout << '(' << p.first << ',' << p.second << ")\n";
}

//------------------------------------------------------------------------------

void print_begin_with(const map<string, int>& words)
{
    cout << "Введите буквы, чтобы узнать "
            "сколько слов содержат их\n";
    string w;
    cin >> w;
    if (!cin) error("bad input");

    auto m{get_str_begin_with(words, w)};
    for (const auto& p : m)
        cout << '(' << p.first << ',' << p.second << ")\n";
}

//------------------------------------------------------------------------------

void print_str_with_count_ch(const map<string, int>& words)
{
    cout << "Введите количество букв, "
            "сколько слов содержат их\n";
    size_t cnt;
    cin >> cnt;
    if (!cin) error("bad input");

    auto m{get_str_with_count_ch(words, cnt)};
    for (const auto& p : m)
        cout << '(' << p.first << ',' << p.second << ")\n";
}

//------------------------------------------------------------------------------

void exercise21_14()
{
    const string fname{"./file"};
    map<string, int> words{get_data_from_file(fname)};
    word_counts(words);
    words_max_times(words);
    long_strs(words);
    short_strs(words);
    print_begin_with(words);
    print_str_with_count_ch(words);
}

//------------------------------------------------------------------------------

int main()
try {
    exercise21_14();
    return 0;
}
catch (const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "oops!";
    return -2;
}

//------------------------------------------------------------------------------
