#ifndef MONEY_H
#define MONEY_H

#include "../../bstroustrup_code/std_lib_facilities.h"

class Money
{
    static constexpr int cent_in_dol = 100;
    static constexpr int def_cent = 1000;
public:    
    Money(int dol, int cen);
    Money(double cent);
    Money();
    int cent_in_dollar() const { return cent_in_dol; }
    int dollar() const
    { return narrow_cast<int>(c / cent_in_dol); }
    int cent() const { return c % cent_in_dol; }
private:
    long c;
};

ostream& operator<<(ostream& os, const Money& m);
istream& operator>>(istream& is, Money& m);
bool is_money(const double &c);
#endif // MONEY_H
