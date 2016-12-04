// exercise14_10
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

struct Pseudo_window : Graph_lib::Window {
    Pseudo_window(Point xy, int w, int h, const string& title);
    void show() {  Fl::run(); }
private:
    Closed_polyline cp;
};

//-----------------------------------------------------------------------------

Pseudo_window::Pseudo_window(Point xy, int w, int h, const string& title)
    : Window(xy,w,h,title)
{
    cp.add(Point{w/2, w/2});
    cp.add(Point{w/2, h/2});
    cp.add(Point{h/2, h/2});
    attach(cp);
}

//-----------------------------------------------------------------------------

void exercise14_10()
{
    Pseudo_window win{Point {0, 0}, 800, 600, "exercise 14_10"};
    win.show();
}

//-----------------------------------------------------------------------------

int main()
try {
    exercise14_10();
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
