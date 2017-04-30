//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

enum class Month {
    jan=1, feb, mar, apr, may, jun,
    jul, aug, sep, oct, nov, dec
};

//------------------------------------------------------------------------------

class Date {
public:
    Date(int y, Month m, int d);
    void add_day(int n);
    Month month() const { return m; }
    int day() const { return d; }
    int year() const  { return y; }
private:
    int y;
    Month m;
    int d;
};

//------------------------------------------------------------------------------

/* struct Date{} - использовалось в 9.4.1 и 9.4.2
struct Date {
    int y; Month m; int d;
    Date(int y, Month m, int d);
    void add_day(int n);
};
*/

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

bool is_date(int y, Month m, int d)
{
    // Полагаем, что y корректен
    if (d<1) return false;
    if (m<Month::jan || Month::dec<m) return false;
    int days_in_month = day_in_month(m);
    if (days_in_month < d) return false;
    return true;
}

//------------------------------------------------------------------------------

Date::Date(int yy, Month mm, int dd)
    :y(yy), m(mm), d(dd)
{
    if(!is_date(y,m,d)) error("Date()", "Неверная дата!");

}

//------------------------------------------------------------------------------
/* Эта ф-ция использовалась в 9.4.1
void init(Date& dd, int y, int m, int d)
{
    // Полагаем, что y корректен
    if (d<1) error("init", "Не корректная дата");
    if (m<1 || 12<m) error("init", "Не корректная дата");
    int days_at_month = day_in_month(Month(m)); // В месяцее не более 31 день
    if (days_at_month < d) error("init", "Не корректная дата");
    dd.d = d;
    dd.m = Month(m);
    dd.y = y;
}*/

//------------------------------------------------------------------------------

Month operator++(Month& m)
{
    m = (m==Month::dec)?Month::jan:Month(int(m)+1);
    return m;
}

//------------------------------------------------------------------------------

void Date::add_day(int n)
{
    if (n < 1)
        error("add_day()", "Не корректное число дней для добавления");

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

/*Эта ф-ция использовалась в 9.4.1
void add_day(Date& dd, int n)
{
    if (n < 1)
        error("add_day()", "Не корректное число дней для добавления");

    int days_at_month = day_in_month(dd.m);
    int delta = days_at_month - dd.d;
    int num_add_month = n / delta;
    //int remainder = n % days_at_month;
    while (true) {
        if (num_add_month == 0) break;
        if (dd.m == Month::dec) {
            dd.m = Month::jan;
            ++dd.y;
        }
        else { ++dd.m;}
        n = n-(days_at_month-dd.d);
        dd.d = 1;
        --n;
        days_at_month = day_in_month(dd.m);
        num_add_month = n / days_at_month;
    }
    if (n==0) return;
    dd.d+=n;
}*/

//------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const Date& d)
{
    return os << '(' << d.year()
              << '.' << int(d.month())
              << '.' << d.day() << ')';
}

//------------------------------------------------------------------------------

void func()
{
    try {
        Date today{1963,Month::dec,31};
        Date tomorrow = today;
        tomorrow.add_day(1);
        cout << tomorrow << '\n';
    }
    catch (exception& e) {
        cerr << "error" << e.what() << '\n';
    }
}

//------------------------------------------------------------------------------

int main()
{
    func();
    keep_window_open("~~");
    return 0;
}

//------------------------------------------------------------------------------

