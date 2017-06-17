//------------------------------------------------------------------------------

#include "Money.hpp"

//------------------------------------------------------------------------------

Money::Money(Currency cur, double num)
    : c{cur}, n{0}
{
    num = round(num*100);
    if (!is_money(num))
        error("Money(): ", "Некорректные деньги!");
    n = num;
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
    return os << m.number();
}

//------------------------------------------------------------------------------

istream& operator>>(istream& is, Money& m)
{
    double d;
    string s;

    is >> d >> s;
    if (!is) { return is; }

    Exchange e;
    m = Money{e(s), d};

    return is;
}

//------------------------------------------------------------------------------

const long& max_long_int()
{
    static const long& lint = pow(2,sizeof(long int) * 8.0 - 1) - 1;
    return lint;
}

//------------------------------------------------------------------------------

void end_of_loop(istream& is, char term, const string& message)
{
    if (is.eof()) {         // Конец ввода
        is.clear();
        return;
    }
    if (is.fail()) {        // Некорректное состояние
        is.clear();
        char c;
        if (is >> c && c==term) return; // Является ли введеный символ
                                        // символом завершения ввода
        error("end_of_loop: ", message);
    }
}

//-----------------------------------------------------------------------------

struct Reading {
    string name;
    double value;
};

//-----------------------------------------------------------------------------

istream& operator>>(istream& is, Reading& r)
{
    char ch1;
    if (is >> ch1 && ch1 != '(') {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    char ch2;
    string s1;
    double v;

    is >> s1 >> v >> ch2;
    if (!is || ch2!=')') error("Плохая запись");

    r.name = s1;
    r.value = v;

    return is;
}

//-----------------------------------------------------------------------------

bool is_exchange(const Exchange& e)
{
    for (int i=0; i < e.currency_count; ++i)
        if (e.value(i) == e.not_reading) return false;
    return true;
}

//-----------------------------------------------------------------------------

void reading_add_to_exch(const Reading& r, Exchange& e)
{
    constexpr int bad_index = -1;
    int currency_index{bad_index};

    for (int i=1; i < e.currency_count; ++i)
        if (e(Currency(i)) == r.name) {
            currency_index = i;
            break;
        }

    if (currency_index == bad_index)
        error("Некорректная валюта!");

    if (e.value(currency_index) != e.not_reading)
        error("Echange: у нас дубль!");

    e.set_value(currency_index, r.value);
}

//-----------------------------------------------------------------------------

istream& operator>>(istream& is, Exchange& e)
{
    char ch1;
    if (is >> ch1 && ch1 != '(') {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    string usd_marker;
    is >> usd_marker;
    if (!is || usd_marker != e(Currency::usd))
        error("Неверное начало Exchange");

    for (Reading r; is >> r;) reading_add_to_exch(r, e);

    if (!is_exchange(e)) error("Некорректный курс");
    end_of_loop(is, ')', "Неправильный конец Exchange");

    return is;
}

//-----------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Exchange& e)
{
    for (int i=0; i < e.currency_count; ++i) {
        os << e.value(i) << ' ' << e(int_to_cur(i));
        if (i != e.currency_count-1)
            os << " == " ;
    }
    return os;
}

//-----------------------------------------------------------------------------

Money get_convert_money(Exchange& e, Money& src, Currency dest)
{
    double res = src.number() *
            e.value(cur_to_int(dest)) / e.value(cur_to_int(src.c));
    return Money{dest, res};
}

//-----------------------------------------------------------------------------
