#ifndef MONEY_H
#define MONEY_H

#include "../../bstroustrup_code/std_lib_facilities.h"

enum class Currency {
    USD, DKK
};

class Money
{
    static constexpr int dec_places = 100;
    static constexpr int def_count = 1000;
public:
    Money(Currency cur, double num);
    Money();
    Currency c;

    double number() const
    { return narrow_cast<double>(1.0*n / dec_places); }

private:
    long n;
};

ostream& operator<<(ostream& os, const Money& m);
istream& operator>>(istream& is, Money& m);
bool is_money(const double &c);
void init_td();
double currency_to_usd(Currency c);
#endif // MONEY_H
