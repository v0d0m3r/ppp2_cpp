//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "Lines_window.h"

//-----------------------------------------------------------------------------

int main()
try {
    Lines_window win{Point{100, 100}, 600, 400, "lines"};
    return gui_main();
}
catch(exception& e) {
    cerr << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "exiting\n";
    return -2;
}

//-----------------------------------------------------------------------------
