//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"

//-----------------------------------------------------------------------------

using namespace Graph_lib;

//-----------------------------------------------------------------------------

int main()
try {    
    Point t1{100, 100};
    Simple_window win{t1, 800, 600, "Canvas"};

    Rectangle r{Point{300, 50}, 100, 30};
    r.set_color(Color::blue);

    Text t{Point{320, 70}, "Howdy!"};

    win.attach(r);
    win.attach(t);
    win.set_label("Canvas");
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
