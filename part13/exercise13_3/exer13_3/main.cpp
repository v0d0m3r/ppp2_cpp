// Exercise 13_2
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void use_arrow()
{

    const Point x{0, 0};
    Simple_window win{x, 800, 600, "Arrow"};

    Arrow arr(Point{400,400}, Point{200,200});
    Arrow arr1(Point{400,400}, Point{100,100}, 25, 30);

    win.attach(arr);
    win.attach(arr1);
    win.wait_for_button();
}

int main()
try {
    use_arrow();
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
