#include "money.h"

void test()
{
    try {
        Money m1{231412};
        cout << m1 << '\n';
    }
    catch (exception &e) {
        cerr << "error: " << e.what() << '\n';
    }
    catch (...) {
        cerr << "Don't now exception!\n";
    }
}

int main()
{

    test();    
    keep_window_open("~~");

    return 0;
}
