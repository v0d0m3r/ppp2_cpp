#include "chrono.h"

using namespace std;

//------------------------------------------------------------------------------

namespace Chrono {

//------------------------------------------------------------------------------

int day_in_month(const Month& n);
Month operator++(Month& m);

// Определения функций-членов
//------------------------------------------------------------------------------

Date::Date(int yy, Month mm, int dd)
    : y{yy}, m{mm}, d{dd}
{
    if(!is_date(y, m, d)) throw Invalid{};
}

//------------------------------------------------------------------------------

const Date& default_date()
{
    static const Date& dd{2001, Month::jan, 1};
    return dd;
}

//------------------------------------------------------------------------------

Date::Date()
    :y{default_date().year()},
     m{default_date().month()},
     d{default_date().day()}
{

}

//------------------------------------------------------------------------------

void Date::add_day(int n)
{
    if (n < 1)
        throw Invalid {};

    int days_at_month = day_in_month(m);
    int delta = days_at_month - d;
    int num_add_month = (delta == 0)
        ? 1 : n/delta;
    while (true) {
        if (num_add_month == 0) break;
        if (m == Month::dec) {
            m = Month::jan;
            ++y;
        }
        else { ++m;}
        n = n-(days_at_month-d);
        d = 1;
        --n;
        days_at_month = day_in_month(m);
        num_add_month = n / days_at_month;
    }
    if (n==0) return;
    d+=n;
}

//------------------------------------------------------------------------------

void Date::add_month(int)
{
    //...
}

//------------------------------------------------------------------------------

void Date::add_year(int n)
{
    if (m==Month::feb && d==29 &&
            !leapyear(y+n)) { // В невисокосный год
        m = Month::mar; // 29 февраля превращается в 1 марта
        d = 1;
    }
    y+=n;
}

// Вспомогательные функции
//------------------------------------------------------------------------------

bool is_date(int y, Month m, int d)
{
    // Полагаем, что y корректен
    if (d<1) return false;
    if (m<Month::jan || Month::dec<m) return false;
    int days_in_month = 31; // В месяце не более 31 дня
    switch (m) {
    case Month::feb:
        days_in_month = (leapyear(y))?29:28;
        break;
    case Month::apr: case Month::jun:
    case Month::sep: case Month::nov:
        days_in_month = 30;
        break;
    default:
        break;
    }
    if (days_in_month < d) return false;
    return true;
}

//------------------------------------------------------------------------------

bool leapyear(int)
{
    // ...
    return 0;
}

//------------------------------------------------------------------------------

bool operator==(const Date& a, const Date& b)
{
    return a.day() == b.day()
           && a.month() == b.month()
           && a.year() == b.year();
}

//------------------------------------------------------------------------------

bool operator!=(const Date& a, const Date& b)
{
    return !(a==b);
}

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.year()
              << '.' << int(d.month())
              << '.' << d.day() << ')';
}

//------------------------------------------------------------------------------

istream& operator>>(istream& is, Date& dd)
{
    int y, m, d;
    char ch1, ch2, ch3, ch4;
    is >> ch1 >> y >> ch2
       >> m >> ch3 >> d >> ch4;
    if (!is) return is;
    if (ch1!='(' || ch2!='.' ||
            ch3!='.' || ch4!=')') {
        is.clear(ios_base::failbit);
        return is;
    }
    dd = Date(y, Month(m), d);
    return is;
}

//------------------------------------------------------------------------------

enum class Day {
    sunday, monday, tuesday, wednesday,
    thursday, friday, saturday
};

//------------------------------------------------------------------------------

Day day_of_week(const Date&)
{
    return Day::monday;
}

//------------------------------------------------------------------------------

Date next_sunday(const Date& d)
{
    return d;
}

//------------------------------------------------------------------------------

Date next_weekday(const Date& d)
{
    return d;
}

//------------------------------------------------------------------------------

int day_in_month(const Month& n)
{
    switch (n) {
    case Month::feb:
        return 29;
    case Month::apr: case Month::jun:
    case Month::sep: case Month::nov:
        return 30;
    default:
        return 31;
    }
}

//------------------------------------------------------------------------------

Month operator++(Month& m)
{
    m = (m==Month::dec)?Month::jan:Month(int(m)+1);
    return m;
}

//------------------------------------------------------------------------------
} // Chrono
