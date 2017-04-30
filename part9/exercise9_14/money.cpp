#include "money.h"

//------------------------------------------------------------------------------

Money::Money(double cent)
    :c{0}
{
    cent = round(cent);
    if (is_money(cent))
        error("Money(): ", "Некорректные деньги!");
    c = cent;
}

//------------------------------------------------------------------------------

Money::Money()
    :c{def_cent}
{
}

//------------------------------------------------------------------------------

const long& max_long_int();

//------------------------------------------------------------------------------

bool is_money(const double& c)
{
    const long& max_lint = max_long_int();
    if (c<0 || c>max_lint) return false;
    return true;
}

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Money& m)
{
    return os << '$' << m.dollar()
              << '.' << m.cent();
}

//------------------------------------------------------------------------------

istream& operator>>(istream& is, Money& m)
{
    char ch1, ch2;
    int d, c;
    is >> ch1 >> d
       >> ch2 >> c;
    if (!is) { return is; }
    if (ch1!='$' || ch2!='.') {
        is.clear(ios_base::failbit);
        return is;
    }
    double cents = d*m.cent_in_dollar()+c;
    m = Money{cents};
    return is;
}

//------------------------------------------------------------------------------

const long& max_long_int()
{
    static const long& lint = pow(2,sizeof(long int) * 8.0 - 1) - 1;
    return lint;
}

//------------------------------------------------------------------------------
