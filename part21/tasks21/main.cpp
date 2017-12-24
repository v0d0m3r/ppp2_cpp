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

template<typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p)
{
    return os << '(' << p.first
              << ',' << p.second << ')';
}

//------------------------------------------------------------------------------

istream& operator>>(istream& is, pair<string, int>& p)
{
    string first;
    int second;

    char ch1, ch2, ch3;
    is >> ch1;

    get_name(first, is);
    if (!is) return is;

    is >> ch2 >> second >> ch3;
    if (!is) return is;

    if (ch1!='(' || ch2!=',' || ch3!=')') {
        // Ошибка формата
        is.clear();
        return is;
    }
    p = make_pair(first, second);
    return is;
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

template<typename T1, typename T2>
void print_map(const map<T1, T2>& m, ostream& os, const string& term)
{
    for (const auto& e : m) os << e << term;
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

int sum(int v, const pair<string, int>& p)
{
    return v + p.second;  // Накапливает итог
}

//------------------------------------------------------------------------------

void task_part2()
{
    map<string, int> msi;
    msi["lecture"] = 21;
    msi["micromax"] = 1;
    msi["leopard"] = 21;
    msi["data tab"] = 3;
    msi["admin card"] = 777;
    msi["dart weider"] = 123;
    msi["stars wars"] = 8;
    msi["cycle"] = 4;
    msi["gepard"] = 333;
    msi["fast"] = 1;

    string term{"\n"};
    print_map(msi, cout, term);

    msi.clear();

    string first;
    int second;
    for (int i{0}; i < 10; ++i) {
        cin >> first >> second;
        if (!cin) break;
        msi[first] = second;
    }
    print_map(msi, cout, term);

    int total{std::accumulate(msi.begin(), msi.end(), 0, sum)};
    cout << "total == " << total << '\n';

    map<int, string> mis;
    for (const auto& p : msi) mis[p.second] = p.first;

    print_map(mis, cout, term);
}

//------------------------------------------------------------------------------

void task_part3()
{
    string from{"./from3.txt"};

    ifstream is{from};

    vector<double> vd{istream_iterator<double>{is},
                      istream_iterator<double>{},
                      std::allocator<double>{}};

    std::copy(vd.begin(), vd.end(),
              ostream_iterator<double>{cout, "\n"});

    vector<int> vi{vd.begin(), vd.end(), std::allocator<int>{}};

    for (Size_type<vector<int>> i{0}; i < vi.size(); ++i)
        cout << vd[i] << '\t' << vi[i] << '\n';

    double total{std::accumulate(vd.begin(), vd.end(), 0.00)};
    cout << "total vd == " << total << '\n';

    double minus_plus {
        std::inner_product(
        vd.begin(), vd.end(),
        vi.begin(),
        0.0,
        minus<double>(),        // Обычное вычитание
        plus<double>())         // Обычное сложение
    };
    cout << "minus_plus == " << minus_plus << '\n';

    reverse(vd.begin(), vd.end());
    std::copy(vd.begin(), vd.end(),
              ostream_iterator<double>{cout, "\n"});
    double mid{total/vd.size()};
    cout << "middle vd == " <<  mid << '\n';

    int count{count_if(vd.begin(), vd.end(),
                       [&](double a) { return a < mid; })};
    vector<double> vd2(count);
    copy_if(vd.begin(), vd.end(), vd2.begin(),
            [&](double a) { return a < mid; });
    std::copy(vd2.begin(), vd2.end(),
              ostream_iterator<double>{cout, "\n"});

    sort(vd.begin(), vd.end());
    std::copy(vd.begin(), vd.end(),
              ostream_iterator<double>{cout, "\n"});
}

//------------------------------------------------------------------------------

int main()
try
{
    //task_part1();
    //task_part2();
    task_part3();
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
