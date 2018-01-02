//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"
#include <unordered_map>
#include <set>

//------------------------------------------------------------------------------

struct Fruit {
    explicit Fruit(string nn = "", int cc = 0, double up = 0.00)
        : name{nn}, count{cc}, unit_price{up} {}

    string name;
    int count;
    double unit_price;
};

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Fruit& f)
{
    return os << '(' << f.name
              << ',' << f.count
              << ',' << f.unit_price << ')';
}

//------------------------------------------------------------------------------

struct Fruit_order {
    bool operator() (const Fruit& a, const Fruit& b) const
    {
        return a.name<b.name;
    }
    bool operator() (const Fruit* const a, const Fruit* const b) const
    {
        if (a==nullptr || b==nullptr) return false;
        return a->name < b->name;
    }
};

//------------------------------------------------------------------------------

void exercise_21_6()
{
    list<Fruit> lf;
    lf.insert(lf.begin(), Fruit{"kiwi", 100, 7.5});
    lf.insert(lf.begin(), Fruit{"quince", 3, 3.2});
    lf.insert(lf.begin(), Fruit{"plum", 8, 32.1});
    lf.insert(lf.begin(), Fruit{"apple", 7, 0.37});
    lf.insert(lf.begin(), Fruit{"grape", 2345, 0.15});
    lf.insert(lf.begin(), Fruit{"orange", 99, 7.3});

    set<Fruit*, Fruit_order> inventory;

    for (auto p{lf.begin()}; p != lf.end(); ++p)
        inventory.insert(&*p);

    for (auto p{inventory.begin()}; p != inventory.end(); ++p)
        if (*p) cout << **p << '\n';

    if (lf.begin() == lf.end()) return;

    auto p{inventory.find(&*lf.begin())};
    if (p!=inventory.end() && *p)
        cout << "I find:\t" << **p << '\n';
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise_21_6();
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
