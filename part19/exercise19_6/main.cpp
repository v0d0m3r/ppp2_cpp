//------------------------------------------------------------------------------

#include "Test.hpp"

//------------------------------------------------------------------------------

void do_test()
{
    vector<User_case<int>> vuc;
    get_test_data(vuc);

    User_case<int> calc;
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

    Number<int> a{33}, b{5};
    // If use: Number<double> a{33}, b{5};
    // We get error: invalid operands of types ‘const double’ and
    // ‘const double’ to binary ‘operator%’() % b.get());
    auto c{a % b};
    cout << "c == " << c << '\n';
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
