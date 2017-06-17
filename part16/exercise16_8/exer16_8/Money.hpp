#ifndef MONEY_H
#define MONEY_H

//-----------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//-----------------------------------------------------------------------------

enum class Currency { usd, rub, eur };

//-----------------------------------------------------------------------------

inline Currency int_to_cur(const int& i)
{
    return narrow_cast<Currency>(i);
}

inline int cur_to_int(const Currency& c)
{
    return narrow_cast<int>(c);
}

//-----------------------------------------------------------------------------
// Содержит значения валют
class Exchange
{
public:
    const double not_reading{-777.00};
    const int currency_count{3};

    Exchange() { value_tb[cur_to_int(Currency::usd)] = 1; }

    // Получаем наименование валюты
    string operator() (Currency c) const
    { return name_tb[cur_to_int(c)]; }

    // Получаем код валюты
    Currency operator() (const string& name) const
    {
        for (size_t i=0; i < name_tb.size(); ++i)
            if (name_tb[i] == name) return int_to_cur(i);
        error("Неправильное имя валюты");
    }

    double value(int i) const
    { return value_tb[i]; }

    void set_value(int i, double v)
    { value_tb[i] = v; }

private:    
    vector<string> name_tb {"usd", "rub", "eur"};
    vector<double> value_tb{vector<double>(currency_count, not_reading)};
};

//-----------------------------------------------------------------------------

istream& operator>>(istream& is, Exchange& e);
ostream& operator<<(ostream& os, const Exchange& e);

//-----------------------------------------------------------------------------

class Money
{
public:
    Money(Currency cur, double num);
    Money() : c{Currency::usd}, n{def_count} {}

    Currency c;

    double number() const
    { return 1.0 * n / dec_places; }

    static constexpr int dec_places{100};
    static constexpr int def_count{1000};

private:
    long n;
};

//-----------------------------------------------------------------------------

bool is_money(const double &c);
Money get_convert_money(Exchange& e, Money& src, Currency dest);

ostream& operator<<(ostream& os, const Money& m);
istream& operator>>(istream& is, Money& m);

//-----------------------------------------------------------------------------

#endif // MONEY_H
