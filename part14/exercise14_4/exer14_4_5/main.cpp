// exercise14_4_5
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void exercise14_4()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 14_4"};

    Immobile_circle ic{Point{100, 100}, 50};
    //ic.move(150, 150);
    Circle& cir{ic};

    win.attach(ic);
    win.wait_for_button();

    cir.move(300, 300);

    win.wait_for_button();
}

//-----------------------------------------------------------------------------

void exercise14_5()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 14_5"};

    Striped_rectangle sr{Point{400, 400}, 300, 300};
    sr.set_fill_color(Color::blue);
    win.attach(sr);
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    //exercise14_4();
    exercise14_5();
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
