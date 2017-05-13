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
    Simple_window win{t1, 200, 300, "Canvas"};

    win.set_label("Canvas");
    win.wait_for_button();

    Point t2{200, 300};
    Simple_window win2{t2, 2000, 300, "Canvas #2"};
    win2.wait_for_button();

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

