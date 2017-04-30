#include "book.h"

//------------------------------------------------------------------------------

const Book& default_book()
{
    static const Book& book{"1-1-1-a", "Hello", "Smith",
                            Chrono::Date{}, Genre::fan,false};
    return book;
}

//------------------------------------------------------------------------------

Book::Book()
    : i  {default_book().isbn()},
      t  {default_book().title()},
      sn {default_book().soname_auth()},
      d  {default_book().date_copyright()},
      g  {default_book().genre()},
      is {default_book().issue()}
{

}

//------------------------------------------------------------------------------

// Проверяет корректность кода ISBN
bool is_isbn(const string& isb)
{
    // ISBN состоит из трех пар: число и "-"
    // Последний символ буква или цифра
    for (int i=isb.size()-1; i>=0; --i)
        cin.putback(isb[i]);

    char ch = 0;
    int part_isbn = 0;

    for (int i=0; i<3; ++i) {
        cin.get(ch);
        // Число должно начинаться с цифры
        if (!isdigit(ch))
            return false;
        cin.putback(ch);
        cin >> part_isbn;   // Должно быть число
        cin.get(ch);        // Должно быть -
        if (ch != '-')
            return false;
    }
    cin.get(ch);            // Цифра или Буква
    if (!isdigit(ch) && !isalpha(ch))
        return false;
    if (ch != isb.back())   // Цифра или Буква является
        return false;       // последним символом?
    return true;
}

//------------------------------------------------------------------------------

// Проверяет корректность фамилии автора
bool is_soname_auth(const string& so)
{
    // Фамилия автора состоит только из букв
    for (size_t i=0; i<so.size(); ++i)
        if (!isalpha(so[i]))
            return false;
    return true;
}

//------------------------------------------------------------------------------

// Проверяет входные данные
bool is_book(const string& isb, const string& so)
{
    if (!is_isbn(isb))
        return false;
    if (!is_soname_auth(so))
        return false;
    return true;
}

//------------------------------------------------------------------------------

Book::Book(string ii, string tt, string snn,
           Chrono::Date dd, Genre gg,bool iss)
    : i(ii), t(tt), sn(snn),
      d(dd), g(gg), is(iss)
{
    if (!is_book(i, sn))
        error("book.cpp: Book(): ", "Ошибка ввода данных о книге!");
}

//------------------------------------------------------------------------------

void Book::set_issue(bool iss)
{
    is = iss;
}

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Book& b)
{
    string status = (b.issue()) ? "выдана" : "не выдана";
    return os << "Название: " << b.title()
              << "\nАвтор: " << b.soname_auth()
              << "\nISBN: " << b.isbn()
              << "\nСтатус: " + status;
}

//------------------------------------------------------------------------------

bool operator==(const Book& a, const Book& b)
{
    return a.isbn() == b.isbn();
}

//------------------------------------------------------------------------------

bool operator!=(const Book& a, const Book& b)
{
    return !(a == b);
}

//------------------------------------------------------------------------------
