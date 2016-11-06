// exercise13_18_19
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void exercise13_18()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 13_18"};
    Poly p = {
        {100, 100}, {150, 200}, {250, 250}, {300, 200}, {100, 100}
    };
    win.attach(p);
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

void exercise13_19()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 13_19"};
    int h = 50;
    int w = 50;
    Vector_ref<Star> vr;
    for (int i=5; i < 10; ++i) {
        vr.push_back(new Star{Point{2*i*w, 150}, i, w, h});
        vr[vr.size()-1].set_fill_color(i);
        win.attach(vr[vr.size()-1]);
    }
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {    
    //exercise13_18();
    exercise13_19();
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
