#include "chrono.h"

class Book
{    
public:
    class Invalid {};   // Для генерации исключений
    Book();
    Book(string isb, string ti, string so,
         Chrono::Date dd, bool is);
    // Получаем данные о книге
    string get_isbn() const { return isbn; }
    string get_title() const { return title; }
    string get_soname_auth() const { return soname_auth; }
    Chrono::Date get_date() const { return date_copyright; }
    bool is_issue() const { return issue; }

private:
    string isbn;
    string title;
    string soname_auth;
    Chrono::Date date_copyright;
    bool issue; // Выдана ли книга?
};
