// exercise14_15
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

struct Iterators {
    int iterator() const { return i; }
    virtual double* next() = 0;
protected:
    void add_iterator()  { ++i; }
private:
    int i{0};
};

//-----------------------------------------------------------------------------

struct Vector_iterator : Iterators {
    Vector_iterator(const vector<double>& vv)
        :v{vv}
    {}

    double* next() override;
private:
    vector<double> v;
};

//-----------------------------------------------------------------------------

double* Vector_iterator::next()
{
    if (v.size()==0 || iterator()>=v.size()) return nullptr;
    add_iterator();
    return &v[iterator()-1];
}

//-----------------------------------------------------------------------------

struct List_iterator : Iterators {
    List_iterator(const list<double>& ll)
        :l{ll}
    {}
    double* next() override;
private:
    list<double> l;
    double dnx = 0.00;
};

//-----------------------------------------------------------------------------

double* List_iterator::next()
{
    if (l.size()==0 || iterator()>=l.size()) return nullptr;
    add_iterator();
    auto nx = std::next(l.begin(), iterator()-1);
    dnx = *nx;
    return &dnx;
}

//-----------------------------------------------------------------------------

void print_iterator(Iterators& iter)
{
    double* dd = iter.next();
    while(dd != nullptr) {
        cout << *dd << '\n';
        dd = iter.next();
    }
}

//-----------------------------------------------------------------------------

void exercise14_15()
{
    vector<double> v;
    for (double i = 11.00; i < 12.00; i+=0.15)
        v.push_back(i);
    Vector_iterator vi{v};
    cout << "print Vector_iterator\n";
    print_iterator(vi);

    list<double> l;
    for (double i = 5.00; i < 7.00; i+=0.15)
        l.push_back(i);
    List_iterator li{l};
    cout << "print List_iterator\n";
    print_iterator(li);
}

//-----------------------------------------------------------------------------

int main()
try {
    exercise14_15();
    keep_window_open("~~");
    return 0;
}
catch(exception& e) {
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return -1;
}
catch (...) {
    cout << "exiting\n";
    keep_window_open("~");
    return -2;
}

//-----------------------------------------------------------------------------
