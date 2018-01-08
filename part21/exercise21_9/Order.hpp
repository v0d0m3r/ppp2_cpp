//------------------------------------------------------------------------------

#ifndef ORDER_HPP
#define ORDER_HPP

//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

struct Purchase {
    Purchase() {}
    Purchase(const string& nm, double up, int cnt)
        : name{nm}, unit_price{up}, count{cnt}
    {
        if (nm.empty() || up<=0 || cnt<=0)
             error("Bad Purchase");
    }

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
    void set_name(const string& name);

    const string& address() const { return addr; }
    void set_address(const string& address);

    const string& date_birth() const { return dbirth; }
    void set_date_birth(const string& date_birth);

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

inline void Order::set_name(const string& name)
{
    if (name.empty())
        error("Bad address client");
    nm = name;
}

//------------------------------------------------------------------------------

inline void Order::set_address(const string& address)
{
    if (address.empty())
        error("Bad address client");
    addr = address;
}

//------------------------------------------------------------------------------

inline void Order::set_date_birth(const string& date_birth)
{
    if (date_birth.empty())
        error("Bad address client");
    dbirth = date_birth;
}

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

template<typename C, typename Pred>
// Требует Container<C>
// и Predicate<Pred, Value_type<C>>
void sort_impl(C& c, Pred pred, std::random_access_iterator_tag)
{
    std::sort(c.begin(), c.end(), pred);
}

//------------------------------------------------------------------------------

template<typename C, typename Pred>
// Требует Container<C>
// и Predicate<Pred, Value_type<C>>
void sort_impl(C& c, Pred pred, std::bidirectional_iterator_tag)
{
    c.sort(pred);
}

//------------------------------------------------------------------------------

template<typename C, typename Pred>
// Требует Container<C>
// и Predicate<Pred, Value_type<C>>
void msort(C& c, Pred pred)
{
    typedef typename std::iterator_traits<Iterator<C>>::iterator_category category;
    sort_impl(c, pred, category());
}

//------------------------------------------------------------------------------

template<class Pred, class E,
         template<class, class...> class C, class... Args>
// Требует Predicate<Pred, E>, Element<E>,
// и Container<C>
void fill_from_file(C<E, Args...>& c, Pred pred, const string& fname)
{
    ifstream ifs{fname};
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);
    if (!ifs)
        error("exercise_21_9: ", "Невозможно открыть входной файл");

    C<E, Args...> tmp{istream_iterator<E>{ifs},
                      istream_iterator<E>{},
                      std::allocator<E>{}};
    msort(tmp, pred);
    c = move(tmp);
}


//------------------------------------------------------------------------------

inline double sum_order(double v, const Order& o)
{
    // Вычисляет сумму всего заказа
    for (int i{0}; i < o.number_of_purchases(); ++i)
        v += o.purchase(i).unit_price * o.purchase(i).count;
    return v;  // Накапливает итог
}

//------------------------------------------------------------------------------

inline double sum_order_alternative(double v, const Order& ord)
{
    // Вычисляет сумму всего заказа
    for (const auto& p : ord)
        v += p.unit_price * p.count;
    return v;  // Накапливает итог
}

//------------------------------------------------------------------------------

#endif // ORDER_HPP

//------------------------------------------------------------------------------
