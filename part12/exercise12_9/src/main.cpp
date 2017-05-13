//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"

//-----------------------------------------------------------------------------

using namespace Graph_lib;

//-----------------------------------------------------------------------------

int main()
try {
    Point t1{0, 0};
    Simple_window win{t1, x_max(), y_max(), "www"};

    Image ii{Point{200, 200}, "www.jpg"};

    Text t{Point{200, 190}, "www!"};
    t.set_font(Graph_lib::Font::times_bold);
    t.set_font_size(20);

    win.attach(ii);
    win.attach(t);
    win.wait_for_button();

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
}

//-----------------------------------------------------------------------------
