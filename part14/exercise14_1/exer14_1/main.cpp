// exercise14_1
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

void exercise14_1()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 14_1"};
    Smiley s{Point{300, 300}, 100};
    win.attach(s);
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    exercise14_1();
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
