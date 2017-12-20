//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

struct Item {
    Item(const string& nn, int id, double vv)
        : name{nn}, iid{id}, value{vv} {}
    string name;
    int iid;
    double value;
};

//------------------------------------------------------------------------------

istream& operator>>(istream& is, Item& ii)
{
    string name;
    int iid;
    double value;
    char ch1, ch2, ch3, ch4;
    is >> ch1 >> name >> ch2 >> iid >> ch3 >> value >> ch4;
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

void task_part1()
{

}

//------------------------------------------------------------------------------

int main()
try
{
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
