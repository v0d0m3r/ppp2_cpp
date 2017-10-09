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

    // Устанавливает итератор на позицию pp в ll-й строке
    Text_iterator(list<Line>::iterator ll, Line::iterator pp)
        : ln{ll}, pos{pp} { }

    reference operator*() { return *pos; }
    Text_iterator& operator++();

    bool operator==(const Text_iterator& other) const
        { return ln==other.ln && pos==other.pos; }

    bool operator!=(const Text_iterator& other) const
        { return !(*this==other); }

    list<Line>::iterator& current_line()
        { return ln; }

    const list<Line>::iterator& current_line() const
        { return ln; }

    Line::iterator& current_pos()
        { return pos; }

    const Line::iterator& current_pos() const
        { return pos; }
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
    {
        auto p{line.end()};
        --p;
        return Text_iterator{p, (*p).end()};
    }
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

void erase_line(Document& d, size_t n)
{
    if (d.line.size()-1<=n) return;
    auto p{d.line.begin()};
    advance(p, n);
    d.line.erase(p);
}

//------------------------------------------------------------------------------

template<typename Iter>
    // Требует Bidirectional_iterator<Iter>
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

// Обработка особых случаев
void proc_extra_case(Document& d, Text_iterator& p,
                     char ch = '\0')
{
    static constexpr char extra{'\n'};
    if (ch==extra && *p!=extra) { // Вставка символа '\n'
                                  // вместо другого
        auto l{d.line.insert(p.current_line(), Line{})};
        auto pos{p.current_pos()};
        ++pos;
        while (pos != p.current_line()->end()) {
            l->push_back(*pos);
            p.current_line()->erase(pos);
        }
    }
    if (ch!=extra && *p==extra) { // Перезапись символа '\n'
                                  // вместо другого
        auto ln{p.current_line()};
        ++ln;

        auto pos{ln->begin()};
        while (pos != ln->end()) {
            p.current_line()->push_back(*pos);
            ln->erase(pos);
        }
        d.line.erase(ln);
    }
}

//------------------------------------------------------------------------------

void find_replace_txt(Document& d,
                      const string& fs, const string& rs)
{
    auto p{find_txt(d.begin(), d.end(), fs)};
    if (p == d.end()) return;

    size_t sz{(fs.size() <= rs.size()) ? rs.size() : fs.size()};
    size_t less{(fs.size() < rs.size()) ? fs.size() : rs.size()};
    for (size_t i{0}; i < sz; ++i) {
        if (i < less) {
            proc_extra_case(d, p, rs[i]);
            *p = rs[i];
            ++p;
        }
        if (fs.size()<rs.size() && less < i) {
            p.current_line()->insert(p.current_pos(), rs[i]);
            proc_extra_case(d, p, rs[i]);
            ++p;
        }
        if (fs.size()>rs.size() && less < i){
                proc_extra_case(d, p);
                p.current_line()->erase(p.current_pos());
        }
    }
}

//------------------------------------------------------------------------------

#endif // DOCUMENT_HPP

//------------------------------------------------------------------------------
