
#include "../../bstroustrup_code/std_lib_facilities.h"

namespace Chrono {
enum class Month {
    jan=1, feb, mar, apr, may, jun,
    jul, aug, sep, oct, nov, dec
};

class Date {
    static const int primary_year = 1970;
    static const Month primary_month = Month::jan;
    static const int primary_day = 1;
public:
    class Invalid {};            // Для генерации исключений
    Date(int y, Month m, int d);
    Date();
    // Копирование по умолчанию нас устраивает

    // Не модифицирующие операции
    int day() const;
    Month month() const;
    int year() const;
    int all_days() const { return days;}
    // Модифицирующие операции
    void add_day(int n);
    void add_month(int n);
    void add_year(int n);
private:
    long int days;
    void convert_to_days(int y, Month m, int d);
};

bool is_date(int y, Month m, int d); // true для корректной даты
bool leapyear(int y);                // true для високосного года
bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);
ostream& operator<<(ostream& os, const Date& d);
istream& operator>>(istream& is, const Date& d);
Date next_sunday(const Date& d);
int week_of_year(const Date& d);
Month int_to_Month(int m);
} // Chrono
