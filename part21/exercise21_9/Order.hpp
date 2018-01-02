//------------------------------------------------------------------------------

#ifndef ORDER_HPP
#define ORDER_HPP

//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

struct Purchase {
    string name;
    double unit_price;
    int count;
};

//------------------------------------------------------------------------------

inline ostream& operator<<(ostream& os, const Purchase& p)
{
    return os << '(' << p.name << ' ' << p.unit_price
              << ' ' << p.count << ')';
}
istream& operator>>(istream& is, Purchase& p);

//------------------------------------------------------------------------------

class Order {
    string nm;
    string addr;
    string dbirth;
    vector<Purchase> vp;
public:
    using iterator = vector<Purchase>::iterator;
    using const_iterator = vector<Purchase>::const_iterator;

    Order() {}
    Order(const string& name, const string& address,
          const string& date_birth,
          const vector<Purchase>& purchases);

    const string& name() const { return nm; }
    void set_name(const string& name) { nm = name; }

    const string& address() const { return addr; }
    void set_address(const string& address) { addr = address; }

    const string& date_birth() const { return dbirth; }
    void set_date_birth(const string& date_birth)
        { dbirth = date_birth; }

    const Purchase& purchase(int i) const { return vp[i]; }
    int number_of_purchases() const
        { return static_cast<int>(vp.size()); }

    void add(const Purchase& p) { vp.push_back(p); }

    iterator begin() { return vp.begin(); }
    const_iterator begin() const { return vp.begin(); }

    iterator end() { return vp.end(); }
    const_iterator end() const { return vp.end(); }
};

//------------------------------------------------------------------------------

inline ostream& operator<<(ostream& os, const Order& ord)
{
    os << '{' << ord.name() << ' ' << ord.address() << ' '
       << ord.date_birth() << ' ';
    for (int i{0}; i < ord.number_of_purchases();  ++i)
         os << ord.purchase(i);
    return os << '}';
}
istream& operator>>(istream& is, Order& ord);

//------------------------------------------------------------------------------

struct Cmp_by_name {
    bool operator() (const Order& a, const Order& b) const
        { return a.name() < b.name(); }
};

//------------------------------------------------------------------------------

struct Cmp_by_addr {
    bool operator() (const Order& a, const Order& b) const
        { return a.address() < b.address(); }
};

//------------------------------------------------------------------------------

#endif // ORDER_HPP

//------------------------------------------------------------------------------
