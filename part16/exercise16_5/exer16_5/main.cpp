//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"


//-----------------------------------------------------------------------------

int main()
try {
    //Figures_window win{Point{100, 100}, 1024, 800, "exercise_16_5"};
    return 0;//gui_main();
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
