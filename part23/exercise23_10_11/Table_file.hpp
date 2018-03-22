//------------------------------------------------------------------------------

#ifndef TABLE_FILE_HPP
#define TABLE_FILE_HPP

//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

template<typename Target, typename Source>
Target m_to(const Source& arg)
{
    stringstream interpreter;
    Target result;
    if (       !(interpreter << arg)    // Запись arg в поток
            || !(interpreter >> result) // Чтение result из потока
            || !(interpreter >> std::ws).eof())
        throw runtime_error{"сбой в m_to<>()"};
    return result;
}

//------------------------------------------------------------------------------

struct Row {    // Данные из строк таблицы
                // в числовом формате
    Row() {}
    Row(int b, int g, int t)
        : boy{b}, girl{g}, total{t} {}
    int boy{0};
    int girl{0};
    int total{0};

    Row& operator+=(const Row& rhs)
    {
        boy   += rhs.boy;
        girl  += rhs.girl;
        total += rhs.total;
        return *this;
    }
};

//------------------------------------------------------------------------------

inline ostream& operator<<(ostream& os, const Row& r)
{
    return os << r.boy << "\t\t" << r.girl << "\t\t" << r.total;
}

//------------------------------------------------------------------------------

using Line_iter = vector<string>::const_iterator;

//------------------------------------------------------------------------------

struct Bad_table_file : std::runtime_error
{
    Bad_table_file(const string& msg)
        : runtime_error{"Bad Table_file: " + msg} {}
};

//------------------------------------------------------------------------------

class Body {  // Объект класса Body указывает
              // на первую и последнюю строки тела таблицы
    Line_iter first;
    Line_iter last;
public:
    Body() {}
    Body(Line_iter p1, Line_iter p2) : first{p1}, last{p2} {}
    Line_iter begin() const { return first; }
    Line_iter end()   const { return last;  }
};

//------------------------------------------------------------------------------

struct Table_file {
    vector<string> lines;        // Строки по порядку
    string name;                 // Имя файла
    Body body;

    Table_file(const string& n); // Чтение файла n в строки
    const string& head() const   // Заголовок
    {
        if (lines.empty())
            throw Bad_table_file{"head(): lines is empty"};
        return lines.front();
    }
    const string& tail() const   // Итоговая строка
    {
        if (lines.empty())
            throw Bad_table_file{"tail(): lines is empty"};
        return lines.back();
    }
    Line_iter begin() const { return body.begin(); }
    Line_iter end()   const { return body.end();   }
};

//------------------------------------------------------------------------------

#endif // TABLE_FILE_HPP

//------------------------------------------------------------------------------
