#include "library.h"

//------------------------------------------------------------------------------

Library::Library()
{
}

//------------------------------------------------------------------------------

void Library::set_patron_paid(bool pay, int ncard)
{
    for (Patron& p : table_patron)
        if (p.num_card() == ncard) {
            p.set_paid(pay);
            cout << "Членские взносы уплачены!\n";
            return;
        }
    cout << "Нет такого пользователя\n";
}

//------------------------------------------------------------------------------

void Library::add_book(const Book& b)
{
    for (size_t i=0; i < table_book.size(); ++i)
        if (table_book[i] == b) {
            error("librarry.cpp: add_book: ",
                  "Такая книга уже есть!");
        }
    table_book.push_back(b);
}

//------------------------------------------------------------------------------

void Library::add_patron(const Patron& p)
{
    for (size_t i=0; i < table_patron.size(); ++i)
        if (table_patron[i] == p) {
            cout << "Повторное добавление Читательского билета!!\n";
            return;
        }
    table_patron.push_back(p);
}

//------------------------------------------------------------------------------

const Patron& get_patron(const vector<Patron>& tp, int ncard)
{
    for (const Patron& p : tp)
        if (p.num_card() == ncard) { // Совпадают номера карточки
            if (p.is_paid())         // Оплачен членский взнос?
                return p;
            else
                error("get_patron: ",
                      "Неоплачен членский взнос!");
        }
    error("get_patron: ", "Нет такого клиента!");
}

//------------------------------------------------------------------------------

Book& get_book(vector<Book>& tb, const string& ti)
{
    int counter = 0;
    for (Book& b : tb)
        if (b.title() == ti) { // Совпадают названия?
            if (!b.issue())    // Выдана книга?
                return b;
            else
                ++counter;
        }
    (counter == 0) ? error("get_book: ", "Нет такой книги: " + ti)
                   : error("get_book: ", "Книга: '" + ti + "' выдана!!");
}

//------------------------------------------------------------------------------

void Library::take_book(int ncard, const string& title)
{
    const Patron& patron = get_patron(table_patron, ncard);
    Book& book = get_book(table_book, title);
    Transaction trans;
    book.set_issue(true);
    trans.book = book;
    trans.patron = patron;
    Chrono::Date d;
    trans.date = d;
    table_tran.push_back(trans);
}

//------------------------------------------------------------------------------

void Library::set_memb_fee(double memb)
{
    for (Patron& p : table_patron)
        p.set_memb_fee(memb);
}

//------------------------------------------------------------------------------

void Library::print_inf_books()
{
    for (const Book& b : table_book)
        cout << "******\n" << b;
    cout << "******\n";
}

//------------------------------------------------------------------------------

vector<string> Library::get_debtors()
{
    vector<string> names;
    for (const Patron& p : table_patron)
            if (!p.is_paid())         // Оплачен членский взнос?
                names.push_back(p.usr_name());
    return names;
}

//------------------------------------------------------------------------------
