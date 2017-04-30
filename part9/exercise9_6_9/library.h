#include "patron.h"

struct Transaction
{
    Book book;
    Patron patron;
    Chrono::Date date;
};

class Library
{
public:
    class Invalid {};
    Library();
    void add_book(const Book& b);
    void add_patron(const Patron& p);    
    void set_patron_paid(bool pay, int ncard);
    void take_book(int ncard, const string& title);
    vector<string> get_debtors();
    void print_inf_books();
    void set_memb_fee(double memb);

private:
    vector<Patron> table_patron;
    vector<Book> table_book;
    vector<Transaction> table_tran;
};
