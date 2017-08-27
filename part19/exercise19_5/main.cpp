//------------------------------------------------------------------------------

#include "Int.hpp"

//------------------------------------------------------------------------------

struct User_case
{
    Int lvl;
    Int rvl;
    Int sum;
    Int sub;
    Int prod;
    Int div;
};

//------------------------------------------------------------------------------

istream& operator>>(istream& is, User_case& u)
    // Предполагаемый формат:
    // ( lvl rvl : сумма разность произведение деление)
{
    char ch1 = 0;
    char ch2 = 0;
    char ch3 = 0;
    User_case uc;

    if (is >> ch1 >> uc.lvl >> uc.rvl
           >> ch2 >> uc.sum >> uc.sub >> uc.prod >> uc.div
           >> ch3) {
        if (ch1!='(' || ch2!=':' || ch3!=')') {
            is.clear(ios_base::failbit);
            return is;
        }
    }
    else
        return is;
    u = uc;
    return is;
}

//------------------------------------------------------------------------------

bool operator==(const User_case& a, const User_case& b)
{
    return     a.lvl  == b.lvl
            && a.rvl  == b.rvl
            && a.sum  == b.sum
            && a.sub  == b.sub
            && a.prod == b.prod
            && a.div  == b.div;
}

//------------------------------------------------------------------------------

bool operator!=(const User_case& a, const User_case& b)
{
    return !(a == b);
}

//------------------------------------------------------------------------------

void get_test_data(vector<User_case>& vuc)
{
    string iname{"./test_data.txt"};
    ifstream ifs{iname};
    if (!ifs) error("Невозможно открыть файл ", iname);

    for (User_case uc; ifs >> uc;) vuc.push_back(uc);
}

//------------------------------------------------------------------------------

void error_test(int i)
{
    error("do_test(): ошибка в " + to_string(i)
          + " наборе теста" );
}

//------------------------------------------------------------------------------

void calculate(User_case& calc, const Int& lvl, const Int& rvl)
{
    calc.lvl  = lvl;
    calc.rvl  = rvl;
    calc.sum  = lvl + rvl;
    calc.sub  = lvl - rvl;
    calc.prod = lvl * rvl;
    calc.div  = lvl / rvl;
}

//------------------------------------------------------------------------------

void do_test()
{
    vector<User_case> vuc;
    get_test_data(vuc);

    User_case calc;
    for (size_t i{0}; i < vuc.size(); ++i) {
        cout << "lvl == "   << vuc[i].lvl
             << "; rvl == " << vuc[i].rvl;

        calculate(calc, vuc[i].lvl, vuc[i].rvl);

        if (calc != vuc[i])
            error_test(i);

        cout << "; sum == "  << calc.sum
             << "; sub == "  << calc.sub
             << "; prod == " << calc.prod
             << "; div == "  << calc.div << '\n';
    }
    cout << "test passed success\n";

}

//------------------------------------------------------------------------------

int main()
try
{
    do_test();
    return 0;
}
catch(exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch(...) {
    cerr << "Oops!";
    return -2;
}

//------------------------------------------------------------------------------
