//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

struct Item {
    explicit Item(const string& nn = "", int id = 0, double vv = 0.00)
        : name{nn}, iid{id}, value{vv} {}
    string name;
    int iid;
    double value;
};

//------------------------------------------------------------------------------

struct Item_order {
    enum Key {
        name, iid, value
    };

    Item_order(const Key& kk) : key{kk} {}

    bool operator() (const Item& a, const Item& b)
    {
        switch (key) {
        case name:  return a.name  < b.name;
        case iid:   return a.iid   < b.iid;
        case value: return a.value < b.value;
        default:
            error("Item_order: not valid key");
        }
    }

    const Key& state() { return key; }
    void reset(const Key& kk) { key = kk; }
private:
    Key key;
};

//------------------------------------------------------------------------------

void get_name(string& name, istream& is)
{
    for (char ch; is.get(ch);) {
        if (ch == ',') {
            is.putback(ch);
            break;
        }
        name += ch;
    }
}

//------------------------------------------------------------------------------

istream& operator>>(istream& is, Item& ii)
{
    string name;
    int iid;
    double value;
    char ch1, ch2, ch3, ch4;
    is >> ch1;

    get_name(name, is);
    if (!is) return is;

    is >> ch2 >> iid >> ch3 >> value >> ch4;
    if (!is) return is;

    if (ch1!='(' || ch2!=',' || ch3!=',' || ch4!=')') {
        // Ошибка формата
        is.clear();
        return is;
    }
    ii = Item{name, iid, value};
    return is;
}

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Item& i)
{
    return os << '(' << i.name
              << ',' << i.iid
              << ',' << i.value << ')';
}

//------------------------------------------------------------------------------

template<typename T>
using is_iter = istream_iterator<T>;

//------------------------------------------------------------------------------

template<typename T>
using os_iter = ostream_iterator<T>;

//------------------------------------------------------------------------------

template<typename C>
void print_contaner(C& c, ostream& os, const string& term)
{
    copy(c.begin(), c.end(), os_iter<Item>{os, term.c_str()});
    cout << "=====================\n";
}

//------------------------------------------------------------------------------

template<typename C>
void sort_impl(C &c, Item_order::Key kk, std::random_access_iterator_tag)
{
    std::sort(c.begin(), c.end(), Item_order{kk});
}

//------------------------------------------------------------------------------

template<typename C>
void sort_impl(C &c, Item_order::Key kk, std::bidirectional_iterator_tag)
{
    c.sort(Item_order{kk});
}

//------------------------------------------------------------------------------

template<typename C>
void sort(C &c, Item_order::Key kk)
{
    typedef typename std::iterator_traits<Iterator<C>>::iterator_category category;
    sort_impl(c, kk, category());
}

//------------------------------------------------------------------------------

template<typename C>
void sort_print_contaner(C& c, ostream& os, const string& term,
                         Item_order::Key kk)
{
    sort(c, kk);
    print_contaner(c, os, term);
}

//------------------------------------------------------------------------------

template<typename C>
Iterator<C> erase(C& c, const string& name)
{
    auto p{find_if(c.begin(), c.end(),
                   [&] (const Item& a)
                   { return a.name == name;})};
    return c.erase(p);
}

//------------------------------------------------------------------------------

template<typename C>
void work_with_list_vector(C& b)
{
    string from{"./from.txt"};

    ifstream is{from};

    for (Item it; is >> it;) b.insert(b.begin(), it);

    string term{"\n"};
    print_contaner(b, cout, term);

    sort_print_contaner(b, cout, term, Item_order::name);
    sort_print_contaner(b, cout, term, Item_order::value);

    b.insert(b.begin(), Item{"horse shoe", 99, 12.34});

    auto itm {find_if(b.begin(), b.end(),
                      [] (const Item& a)
                      { return a.name == "chocolate";})};

    b.insert(itm, Item{"Cannon S400", 9988, 499.95});
    print_contaner(b, cout, term);

    erase(b, "horse shoe");
    erase(b, "chocolate");
    print_contaner(b, cout, term);
}

//------------------------------------------------------------------------------

void task_part1()
{
    vector<Item> vi;
    list<Item> li;

    work_with_list_vector(vi);
    cout << "list here\n";
    work_with_list_vector(li);
}

//------------------------------------------------------------------------------

int main()
try
{
    task_part1();
    return 0;
}
catch (const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "oops!";
    return -2;
}

//------------------------------------------------------------------------------
