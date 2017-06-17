//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "simple_figures_window.h"

//-----------------------------------------------------------------------------

int main()
try {
    Simple_figures_window win{Point{100, 100}, 1024, 700, "exercise_16_5"};
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
