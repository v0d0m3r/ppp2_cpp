// exercise13_10_11
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void paint_regular_poly()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 13_10"};

    Regular_polygon heptagon{Point{300, 300}, 8, 200};
    win.attach(heptagon);
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

void paint_ellipse()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 13_11"};
    Ellipse el{Point{600, 400}, 150, 100};

    Axis xa{Axis::x, Point{el.center().x-200, el.center().y}, 400, 0, "x axis"};
    Axis ya{Axis::y, Point{el.center().x, el.center().y+150}, 300, 0, "y axis"};

    Mark f1{el.focus1(), 'f'};
    Mark f2{el.focus2(), 'f'};

    Line l1{Point{720, 459}, el.focus1()};
    Line l2{Point{720, 459}, el.focus2()};

    win.attach(el);
    win.attach(xa);
    win.attach(ya);
    win.attach(f1);
    win.attach(f2);
    win.attach(l1);
    win.attach(l2);
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    paint_regular_poly();
    paint_ellipse();
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
