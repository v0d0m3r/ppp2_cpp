//------------------------------------------------------------------------------

#include "../exercise21_13/Clear_punctstream.hpp"

//------------------------------------------------------------------------------

inline int get_word_counts(const map<string, int>& words, const string& s)
{
    auto p{words.find(s)};
    if (p == words.end()) return 0;
    return p->second;
}

//------------------------------------------------------------------------------

template<typename A, typename B>
struct Cmp_by_second {
    bool operator() (const pair<A, B>& p, const pair<A, B>& p1) const
    { return p.second < p1.second; }
};

//------------------------------------------------------------------------------

class Longer_than {
    pair<string, int> s{"", 0};
public:
    explicit Longer_than(const string& ss) : s{make_pair(ss, 0)} {}
    void operator() (const pair<string, int>& ss)
    {
        if (ss.first.size() > s.first.size())
            s = ss;
    }
    const pair<string, int>& state() const
    { return s; }
};

//------------------------------------------------------------------------------

class Shorter_than {
    pair<string, int> s{"", 0};
public:
    explicit Shorter_than(const string& ss)
        : s{make_pair(ss, 0)} {}
    void operator() (const pair<string, int>& ss)
    {
        if (ss.first.size() < s.first.size())
            s = ss;
    }
    const pair<string, int>& state() const
    { return s; }
};

//------------------------------------------------------------------------------

template<typename N>
class Equal_digit {
    N s;
public:
    Equal_digit(N ss) : s{ss} {}
    bool operator() (const pair<string, int>& ss) const
        { return ss.first.size() == s; }
};

//------------------------------------------------------------------------------

class Start_with {
    string s;
public:
    Start_with(const string& ss) : s{ss} {}
    bool operator() (const pair<string, int>& ss) const
        { return ss.first.find(s); }
};

//------------------------------------------------------------------------------

class Count_ch {
    size_t sz;
public:
    Count_ch(size_t ss) : sz{ss} {}
    bool operator() (const pair<string, int>& ss) const
        { return ss.first.size() == sz; }
};

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

auto get_words_max_times(const map<string, int>& words)
{
    auto p{words.begin()};
    vector<pair<string, int>> max_times;
    while (true) {
        p = max_element(p, words.end(),
                        Cmp_by_second<string, int>{});
        if (p == words.end()) break;
        max_times.push_back(*p);
        ++p;
    }
    return max_times;
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

template<typename Pred>
auto get_long_str(const map<string, int>& words, Pred p)
{
    Pred l{for_each(words, p)}; // Первое самое длинное
                                // слово
    vector<pair<string, int>> long_str_tb;    // Таблица самых длинных слов
    // Находим остальные слова
    for (auto p{words.begin()}; p != words.end(); ++p) {
        p = find_if(p, words.end(), Equal_digit{l.state().first.size()});
        if (p != words.end())
            long_str_tb.push_back(*p);
    }
    return long_str_tb;
}

//------------------------------------------------------------------------------

void long_strs(const map<string, int>& words)
{
    auto long_str_tb{get_long_str(words, Longer_than{""})};
    cout << "long str:\n";
    for (const auto& p : long_str_tb)
        cout << '(' << p.first << ',' << p.second << ")\n";
}

//------------------------------------------------------------------------------

void short_strs(const map<string, int>& words)
{
    auto short_str_tb{get_long_str(words, Shorter_than{""})};
    cout << "long str:\n";
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

    map<string, int> m;
    copy_if(words.begin(), words.end(),
            std::inserter(m, std::next(m.begin())), Start_with{w});

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

    map<string, int> m;
    copy_if(words.begin(), words.end(),
            std::inserter(m, std::next(m.begin())), Count_ch{cnt});

    for (const auto& p : m)
        cout << '(' << p.first << ',' << p.second << ")\n";
}

//------------------------------------------------------------------------------

void exercise21_14()
{
    map<string, int> words{get_data_from_file()};
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
