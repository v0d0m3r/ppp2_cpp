//------------------------------------------------------------------------------

#include "Order.hpp"

//------------------------------------------------------------------------------

Order::Order(const string& name, const string& address,
             const string& date_birth, const vector<Purchase>& purchases)
    : nm{name}, addr{address}, dbirth{date_birth}, vp{purchases}
{
    if (nm.empty() || addr.empty() || dbirth.empty())
        error("Bad Order");
}

//------------------------------------------------------------------------------

void end_of_loop(istream& is, char term, const string& message)
{
    if (is.fail()) {
        is.clear();
        char ch;
        if (is >> ch && ch==term) return;
        error("end_of_loop: ", message);
    }
}

//------------------------------------------------------------------------------

istream& operator>>(istream& is, Purchase& p)
// Считываем данные покупки из потока is в p
// Формат: ( coca-cola 23.20 5 )
// Проверяем формат, но не корректность данных
{
    char ch1;
    if (is >> ch1 && ch1 != '(') { // Может ли это быть Purchase
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }
    char ch2;
    string nm;
    double pr;
    int cnt;

    is >> nm >> pr >> cnt >> ch2;
    if (!is && ch2!=')')
        error("Плохая запись Purchase");

    p.name = nm;
    p.unit_price =  pr;
    p.count = cnt;
    return is;
}

//------------------------------------------------------------------------------

bool is_valid(const Purchase& p)
{
    if (p.name.empty() || p.unit_price<=0 || p.count<=0)
        return false;
    return true;
}

//------------------------------------------------------------------------------

// Считываем данные заказа из потока is в ord
// Формат: { John NewYork,NY10003 20171221 ....}
// Строгая гарантия
istream& operator>>(istream& is, Order& ord)
{
    char ch1 = 0;
    is >> ch1;
    if (ch1 != '{') { // Может ли это быть Order
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }
    string nm;
    string addr;
    string dbirth;
    is >> nm >> addr >> dbirth;
    if (!is) error("Плохая запись Order");

    int invalids{0};
    Order tmp{nm, addr, dbirth, vector<Purchase>{}};
    for (Purchase p; is >> p;)
        if (is_valid(p)) tmp.add(p);
        else             ++invalids;

    if (invalids)
        error("Неверные данные в Order, всего ", invalids);

    end_of_loop(is, '}', "Неправильный конец Order");

    ord = std::move(tmp);
    return is;
}

//------------------------------------------------------------------------------
