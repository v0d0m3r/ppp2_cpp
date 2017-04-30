#include "chrono.h"

//------------------------------------------------------------------------------

namespace Chrono {

//------------------------------------------------------------------------------

int day_in_month(const Month& n, int y);
Month operator++(Month& m);

// Определения функций-членов
//------------------------------------------------------------------------------

Date::Date(int yy, Month mm, int dd)
    : y{yy}, m{mm}, d{dd}
{
    if(!is_date(y, m, d))
        error("Date(): ", "Некорректная дата!" );
}

//------------------------------------------------------------------------------

const Date& default_date()
{
    static const Date& dd{2016, Month::apr, 17};
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
        error("add_day: ", "Некорректное количество дней!");

    while (day_in_month(m, y) < n) {
       add_month(1);
       n -= day_in_month(m, y);
    }
    d+=n;
}

//------------------------------------------------------------------------------

void Date::add_month(int n)
{
    if (n < 1)
        error("add_month: ", "Некорректное количество месяцев!");

    int num_year = n / int(Month::dec);
    int days = 0;
    for (int i=1; i <= num_year; ++i) {
        y += i;
        for (int j=1; j <= int(Month::dec); ++j ){
            days += day_in_month(Month(j), y);
        }
    }

    if (num_year != 0) {
        y+=num_year;
        n %= int(Month::dec);
    }


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
    if (d < 1) return false;
    if (y < 1) return false;
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
    for (int i=1; i < d.year(); ++i) {
        if (leapyear(i))    // Високосный ли год?
            count_days += 366;
        else
            count_days += 365;
    }
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
    return d;
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
} // Chrono
