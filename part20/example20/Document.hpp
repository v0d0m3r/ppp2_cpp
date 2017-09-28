//------------------------------------------------------------------------------

#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

using Line = vector<char>;  // Строка это вектор символов

//------------------------------------------------------------------------------

class Text_iterator {   // Отслеживает строку и
                        // позицию символа в строке
    list<Line>::iterator ln;
    Line::iterator pos;
public:
    using difference_type = ptrdiff_t;
    using value_type = char;
    using pointer = char*;
    using reference = char&;
    using iterator_category = input_iterator_tag;

    // Устанавливает итератор на позицию pp в l1-й строке
    Text_iterator(list<Line>::iterator l1, Line::iterator pp)
        : ln{l1}, pos{pp} { }

    reference operator*() { return *pos; }
    Text_iterator& operator++();

    bool operator==(const Text_iterator& other) const
        { return ln==other.ln; }

    bool operator!=(const Text_iterator& other) const
        { return !(*this==other); }
};

//------------------------------------------------------------------------------

inline Text_iterator& Text_iterator::operator++()
{
    ++pos;                      // Переход к новому символу
    if (pos == (*ln).end()) {
        ++ln;                   // Переход на новую строку
        pos = (*ln).begin();
    }
    return *this;
}

//------------------------------------------------------------------------------

struct Document {
    list<Line> line;
    Document()  { line.push_back(Line{}); }

    Text_iterator begin()   // Первый символ первой строки
        { return Text_iterator{line.begin(), (*line.begin()).begin()}; }

    Text_iterator end()     // За последним символом элемента
        { return Text_iterator{line.end(), (*line.end()).end()}; }
};

//------------------------------------------------------------------------------

istream& operator>>(istream& is, Document& d)
{
    for (char ch; is.get(ch); ) {
        d.line.back().push_back(ch);    // Добавление символа
        if (ch == '\n')
            d.line.push_back(Line{});   // Добавление строки
    }
    if (d.line.back().size())           // Добавление последней
        d.line.push_back(Line{});       // пустой строки
    return is;
}

//------------------------------------------------------------------------------

void print(Document& d)
{
    for (auto p : d) cout << p;
}

//------------------------------------------------------------------------------

void erase_line(Document& d, int n)
{
    if (n<0 || d.line.size()-1<=n) return;
    auto p{d.line.begin()};
    advance(p, n);
    d.line.erase(p);
}

//------------------------------------------------------------------------------

template<typename Iter>     // Требует Forward_iterator<Iter>
void advance(Iter& p, int n)
{
    if (0 < n) while (0 < n) { ++p; --n; }
    else       while (n < 0) { --p; ++n; }
}

//------------------------------------------------------------------------------

bool match(Text_iterator first, Text_iterator last,
           const string& s)
{
    auto p{first};
    for (auto ch : s) {
        if (p==last || *p != ch) return false;
        ++p;
    }
    return true;
}

//------------------------------------------------------------------------------

Text_iterator find_txt(Text_iterator first,
                       Text_iterator last, const string& s)
{
    if (s.size() == 0) return last; // Нельзя искать пустую строку
    char first_char{s[0]};
    while (true) {
        auto p{find(first, last, first_char)};
        if (p==last || match(p, last, s)) return p;
        first = ++p;                // Ищем следующее вхождение символа
    }
}

//------------------------------------------------------------------------------

#endif // DOCUMENT_HPP

//------------------------------------------------------------------------------
