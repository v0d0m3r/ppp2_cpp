#include "Test_facilities.hpp"

//------------------------------------------------------------------------------

void do_test(Fct_tst fct, const string& name)
try {
    string s{ "*********************\n"};
    cout << s + "start case: " << name << '\n';

    fct();

    cout << "passed succes!\n";
}
catch (...) {
    cout << "bad case!!!!!!!";
    throw;
}

//------------------------------------------------------------------------------
