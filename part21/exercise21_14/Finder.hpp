//------------------------------------------------------------------------------

#ifndef FINDER_HPP
#define FINDER_HPP

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
        { return ss.first.find(s) == 0; }
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

inline auto get_max_often_word(const map<string, int>& words)
{
    return max_element(words, Cmp_by_second<string, int>{});
}

//------------------------------------------------------------------------------

inline auto get_words_max_times(const map<string, int>& words)
{
    vector<pair<string, int>> max_times;
    auto p{get_max_often_word(words)};  // Первый самый частый элемент
    auto often{*p};
    while (p != words.end()) {          // Если нашли, ищем остальные
        max_times.push_back(*p);
        ++p;
        p = find_if(p, words.end(),
                    [&] (const pair<string, int>& p)
                    { return p.second ==  often.second; });
    }
    return max_times;
}

//------------------------------------------------------------------------------

template<typename Pred>
auto get_long_str(const map<string, int>& words, Pred pred)
{
    map<string, int> long_str_tb;  // Таблица самых
                                   // длинных слов
    Pred l{for_each(words, pred)}; // Первое слово, удовлетворяющее
                                   // предикату
    auto p{words.find(l.state().first)};
    // Находим остальные слова
    while (p != words.end()) {
        long_str_tb.insert(*p);
        ++p;
        p = find_if(p, words.end(),
                    Equal_digit{l.state().first.size()});
    }
    return long_str_tb;
}

//------------------------------------------------------------------------------

inline auto get_str_with_count_ch(const map<string, int>& words,
                                  size_t cnt)
{
    map<string, int> m;
    copy_if(words.begin(), words.end(),
            std::inserter(m, m.begin()), Count_ch{cnt});
    return m;
}

//------------------------------------------------------------------------------

inline auto get_str_begin_with(const map<string, int>& words,
                               const string& w)
{
    map<string, int> m;
    copy_if(words.begin(), words.end(),
            inserter(m, m.begin()), Start_with{w});
    return m;
}

//------------------------------------------------------------------------------



//------------------------------------------------------------------------------

#endif // FINDER_HPP

//------------------------------------------------------------------------------
