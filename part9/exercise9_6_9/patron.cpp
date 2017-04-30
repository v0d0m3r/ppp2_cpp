#include "patron.h"

//------------------------------------------------------------------------------

const Patron& default_patron()
{
    static const Patron& patron{"user", 1, 100, false};
    return patron;
}

//------------------------------------------------------------------------------

Patron::Patron()
    : uname (default_patron().usr_name()),
      ncard (default_patron().num_card()),
      memb  (default_patron().memb_fee()),
      pay   (default_patron().is_paid())
{
}

//------------------------------------------------------------------------------

bool is_patron(const string& uname, const int& ncard,
               const double& memb)
{
    // Имя пользователя состоит
    // только из цифр и букв
    for (size_t i=0; i < uname.size(); ++i)
        if (!isalpha(uname[i])
                && !isdigit(uname[i]))
            return false;
    if (ncard<1 || memb<0)
        return false;
    return true;
}

//------------------------------------------------------------------------------

Patron::Patron(string u, int n, double m, bool p)
    :uname(u), ncard(n), memb(m), pay(p)
{
    if (!is_patron(uname, ncard, memb)) throw Invalid {};
}

//------------------------------------------------------------------------------

void Patron::set_memb_fee(double new_memb)
{
    if (new_memb < 0)
        error("patron.cpp: set_memb_fee: ",
              "Некорректное значение членского взноса!");
    memb = new_memb;
}

//------------------------------------------------------------------------------

void Patron::set_paid(bool p)
{
    pay = p;
}

//------------------------------------------------------------------------------

bool operator==(const Patron& a, const Patron& b)
{
    return a.num_card() == b.num_card();
}

//------------------------------------------------------------------------------

bool operator!=(const Patron& a, const Patron& b)
{
    return !(a==b);
}

//------------------------------------------------------------------------------
