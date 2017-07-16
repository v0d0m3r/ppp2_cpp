//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

char gvar{0};
char gvar1{0};

//------------------------------------------------------------------------------

void analize_memory()
{
    cout << "address glob:   " << static_cast<void*>(&gvar) << '\n'
         << "address glob1:  " << static_cast<void*>(&gvar1) << '\n';

    static char stat_var{0};
    static char stat_var1{0};
    cout << "address stat:   " << static_cast<void*>(&stat_var) << '\n'
         << "address stat1:  " << static_cast<void*>(&stat_var1) << '\n';

    char loc_var{0};
    char loc_var1{0};
    cout << "address loc:    " << static_cast<void*>(&loc_var) << '\n';
    cout << "address loc1:   " << static_cast<void*>(&loc_var1) << '\n';

    char* dyn = new char[2];
    char* dyn1 = new char;

    cout << "address dyn[0]: " << static_cast<void*>(dyn) << '\n';
    cout << "address dyn[1]: " << static_cast<void*>(dyn+1) << '\n';
    cout << "address dyn1:   " << static_cast<void*>(dyn1) << '\n';

    delete[] dyn;
    delete dyn1;
}

//------------------------------------------------------------------------------

int main()
try
{
    analize_memory();
    return 0;
}
catch(exception& e) {
    cout << "error: " << e.what() << '\n';
}
catch(...) {
    cerr << "Oops!";
}

//------------------------------------------------------------------------------
