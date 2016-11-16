// exercise14_6_7
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void exercise14_6()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 14_6"};
    Striped_circle sc{Point{400, 400}, 300};
    sc.set_fill_color(Color::blue);
    sc.set_style(Line_style(Line_style::solid, 5));
    win.attach(sc);
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {

    exercise14_6();
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
