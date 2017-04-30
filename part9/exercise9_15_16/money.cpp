#include "money.h"

//------------------------------------------------------------------------------

Money::Money(Currency cur, double num)
    : c{cur}, n{0}
{
    num = round(num*100);
    if (is_money(num))
        error("Money(): ", "Некорректные деньги!");
    n = num;
    init_td();
}

//------------------------------------------------------------------------------

Money::Money()
    : c{Currency::USD}, n{def_count}
{
    init_td();
}

//------------------------------------------------------------------------------

vector<double> tab_defin;

//------------------------------------------------------------------------------

void init_td()
{
    tab_defin.push_back(1.00);
    tab_defin.push_back(6.59);
}

const long& max_long_int();

//------------------------------------------------------------------------------

bool is_money(const double& c)
{
    const long& max_lint = max_long_int();
    if (c<0 || c>max_lint) return false;
    return true;
}

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Money&)
{
    return os; /*<< '$' << m.dollar()
              << '.' << m.cent();*/
}

//------------------------------------------------------------------------------

istream& operator>>(istream& is, Money&)
{
    /*char ch1, ch2;
    int d, c;
    is >> ch1 >> d
       >> ch2 >> c;
    if (!is) { return is; }
    if (ch1!='$' || ch2!='.') {
        is.clear(ios_base::failbit);
        return is;
    }
    double cents = d*m.cent_in_dollar()+c;
    m = Money{cents};*/
    return is;
}

Money operator+(const Money& m1, const Money& m2)
{
    double cur_in_usd1 = currency_to_usd(m1.c);
    double cur_in_usd2 = currency_to_usd(m2.c);
    double sum = cur_in_usd1*m1.number() + cur_in_usd2*m2.number();
    sum /= cur_in_usd1;
    return Money{m1.c, sum};
}

//------------------------------------------------------------------------------

const long& max_long_int()
{
    static const long& lint = pow(2,sizeof(long int) * 8.0 - 1) - 1;
    return lint;
}

//------------------------------------------------------------------------------

double currency_to_usd(Currency c)
{
    return tab_defin[int(c)];
}
