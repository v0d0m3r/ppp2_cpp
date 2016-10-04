// Exercise 13_1
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void use_arc()
{
    Arc a1{Point{200, 200}, 50, 50};
    Arc a2{Point{200, 200}, 100, 50};
    Arc a3{Point{200, 200}, 100, 150};

    const Point x{0, 0};
    Simple_window win{x, 800, 600, "arc"};
    a1.set_end_angle(180);
    win.attach(a1);
    win.attach(a2);
    win.attach(a3);
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    use_arc();
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

