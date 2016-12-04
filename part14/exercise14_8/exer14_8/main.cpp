// exercise14_8
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void exercise14_8()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 14_8"};
    Regular_octagon ro{Point{500,500}, 200};
    ro.center();
    ro.color();
    //ro.draw();
    //ro.draw_lines();
    ro.fill_color();
    ro.move(50,50);
    ro.number_of_points();
    ro.point(0);
    ro.radius();
    ro.set_color(Color::blue);
    ro.set_fill_color(Color::cyan);
    ro.set_style(Line_style::dash);
    ro.sides();
    ro.style();
    //ro.add(Point{0,0});
    //ro.set_point(0, Point{0,0});


    win.attach(ro);
    win.wait_for_button();

}

//-----------------------------------------------------------------------------

int main()
try {
    exercise14_8();
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
