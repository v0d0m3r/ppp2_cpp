#include "chrono.h"

//------------------------------------------------------------------------------

namespace Chrono {

//------------------------------------------------------------------------------

int day_in_month(const Month& n, int y);
Month operator++(Month& m);

// Определения функций-членов
//------------------------------------------------------------------------------

Date::Date(int y, Month m, int d)
    : days(0)
{
    if(!is_date(y, m, d)) throw Invalid{};
    convert_to_days(y, m, d);
}

//------------------------------------------------------------------------------

void Date::convert_to_days(int y, Month m, int d)
{    
    for (int i=primary_year; i < y; ++i)
        (leapyear(i)) ? days+=366 : days+=365;

    for (Month i = Month::jan; i < m; ++i)
        days += day_in_month(i,y);

    days += d;
}

//------------------------------------------------------------------------------

int Date::year() const
{
    int y = 0;
    int delta_year = days;
    bool flag = true;
    while(flag) {
        switch (delta_year) {
        case 365:
        {
            if (leapyear(y))
                flag = false;
            else {
                delta_year -= 365;
                ++y;
            }
            break;
        }
        default:
        {
            if (delta_year > 365) {
                (leapyear(y)) ? delta_year -= 366
                              : delta_year -= 365;
                ++y;
            }
            else
                flag = false;
        }
        }
    }
    y += primary_year;
    return y;
}

//------------------------------------------------------------------------------

Month Date::month() const
{
    if (days == 0)
        return Month::jan;

    int y = year();
    int day_in_year = 0;
    for (int i=primary_year; i < y; ++i)
        (leapyear(i)) ? day_in_year+=366 : day_in_year+=365;

    int residue = days - day_in_year;
    int day_at_month = 0;
    for (Month i = Month::jan; i <= Month::dec; ++i) {
        day_at_month = day_in_month(i, y);
        if (day_at_month > residue)
            return i;
        else
            residue -= day_in_month(i,y);
    }
    throw runtime_error("chrono.cpp: month()");
}

//------------------------------------------------------------------------------

int Date::day() const
{
    if (days == 0)
        return 1;

    int y{year()};
    Month m{month()};

    int day_in_year = 0;
    for (int i=primary_year; i < y; ++i)
        (leapyear(i)) ? day_in_year+=366 : day_in_year+=365;

    int day_at_month = 0;
    for (Month i = Month::jan; i < m; ++i) {
        day_at_month += day_in_month(i,y);
    }

    int d = days - day_in_year - day_at_month;
    return (d == 0) ? 1 : d;
}

//------------------------------------------------------------------------------

const Date& default_date()
{
    static const Date& dd{2016, Month::apr, 19};
    return dd;
}

//------------------------------------------------------------------------------

Date::Date()
    :days{default_date().all_days()}
{

}

//------------------------------------------------------------------------------

void Date::add_day(int n)
{
    if (n < 1)
        throw Invalid{};
    days += n;
}

//------------------------------------------------------------------------------

void Date::add_month(int n)
{
    if (n < 1)
        throw Invalid{};
    Month m = month();
    for (int i=0; i < n; ++i) {
        days += day_in_month(m, year());
        ++m;        
    }
}

//------------------------------------------------------------------------------

void Date::add_year(int n)
{
    if (n < 1)
        throw Invalid{};
    int y = year() + n;
    int day_in_year = 0;
    for (int i = year(); i < y; ++i)
        (leapyear(i)) ? day_in_year+=366 : day_in_year+=365;
    days += day_in_year;
}

// Вспомогательные функции
//------------------------------------------------------------------------------

bool is_date(int y, Month m, int d)
{
    // год начинается с 1970
    if (y < 1970) return false;    
    if (d < 1) return false;
    if (day_in_month(m,y) < d) return false;

    return true;
}

//------------------------------------------------------------------------------

bool leapyear(int y)
{
    return (y%100 == 0) ? (y%400 == 0) : (y%4 == 0);
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

Day day_of_week(const Date& d)
{
    int count_days = 0;
    // Расчет дней, прошедших
    // за количество полных лет
    for (int i=1; i < d.year(); ++i)
        (leapyear(i))   // Високосный ли год?
                ? count_days += 366
                : count_days += 365;
    // Прибавляем количество дней за
    // текущий (неполный год) в зависимости от месяца
    for (int i=1; i < int(d.month()); ++i) {
        count_days += day_in_month(Month(i),d.year());
    }
    // Прибавляем число дней указанных в дате
    count_days+=d.day();
    return Day(count_days%7);
}

//------------------------------------------------------------------------------

Date next_sunday(const Date& d)
{
    constexpr int max_day_of_week = 7;
    Date next_date = d;
    switch (day_of_week(d)) {
    case Day::sunday:
        next_date.add_day(max_day_of_week);
        break;
    case Day::monday:
        next_date.add_day(max_day_of_week-int(Day::monday));
        break;
    case Day::tuesday:
        next_date.add_day(max_day_of_week-int(Day::tuesday));
        break;
    case Day::wednesday:
        next_date.add_day(max_day_of_week-int(Day::wednesday));
        break;
    case Day::thursday:
        next_date.add_day(max_day_of_week-int(Day::thursday));
        break;
    case Day::friday:
        next_date.add_day(max_day_of_week-int(Day::friday));
        break;
    case Day::saturday:
        next_date.add_day(max_day_of_week-int(Day::saturday));
        break;
    default:
        throw runtime_error("next_sunday: Ошибка");
    }
    return next_date;
}

//------------------------------------------------------------------------------

Date next_weekday(const Date& d)
{
    Date weekday = d;
    switch (day_of_week(d)) {
    case Day::sunday: case Day::monday: case Day::tuesday:
    case Day::wednesday: case Day::thursday:
        weekday.add_day(1);
        break;
    case Day::friday:
        weekday.add_day(3);
        break;
    case Day::saturday:
        weekday.add_day(2);
        break;
    default:
        throw runtime_error("next_weekday: Ошибка");
    }
    return weekday;
}

//------------------------------------------------------------------------------

int day_in_month(const Month& n, int y)
{
    switch (n) {
    case Month::feb:
        return (leapyear(y))?29:28;
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

int week_of_year(const Date& d)
{
    Date first_day{ d.year(), Month::jan, 1};
    int count_week = 1;
    while (true) {
        if (first_day.month()==d.month()
                && first_day.day()<d.day()) break;
        first_day = next_sunday(first_day);
        ++count_week;
    }
    return count_week;
}

//------------------------------------------------------------------------------
} // Chrono
