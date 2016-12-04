// exercise14_11
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void exercise14_11()
{
    Simple_window win{Point {0, 0}, 800, 600, "exercise 14_11"};
    Binary_tree bt{Point{100,200}, 4, 600};

    win.attach(bt);
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    exercise14_11();
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
