// exercise13_14-17
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void exercise13_14()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 13_10"};

    Regular_polygon heptagon{Point{300, 300}, 8, 200};
    win.attach(heptagon);
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    exercise13_14();
    //exercise13_15();
    //exercise13_16();
    //exercise13_17();
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
