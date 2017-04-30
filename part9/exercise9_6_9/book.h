#include "chrono.h"

enum class Genre {
    fan, pros, period, biogr, kid
};

class Book
{
public:
    class Invalid {};   // Для генерации исключений
    Book();
    Book(string i, string t, string sn,
         Chrono::Date d, Genre g, bool is);
    // Получаем данные о книге
    string isbn() const { return i; }
    string title() const { return t; }
    string soname_auth() const { return sn; }
    Chrono::Date date_copyright() const { return d; }
    Genre genre() const { return g; }
    bool issue() const { return is; } // true - значит выдана!
    void set_issue(bool iss);

private:
    string i;
    string t;
    string sn;
    Chrono::Date d;
    Genre g;
    bool is; // Выдана ли книга?
};

ostream& operator<<(ostream& os, const Book& b);
bool operator==(const Book& a, const Book& b);
bool operator!=(const Book& a, const Book& b);
