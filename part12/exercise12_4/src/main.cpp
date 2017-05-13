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

    constexpr int square_width = 100;   // Square: width = height

    Rectangle r1{Point{100, 100}, square_width, square_width};

    Rectangle r2{Point{200, 100}, square_width, square_width};
    r2.set_fill_color(Color::red);

    Rectangle r3{Point{300, 100}, square_width, square_width};

    Rectangle r4{Point{300, 200}, square_width, square_width};
    r4.set_fill_color(Color::red);

    Rectangle r5{Point{300, 300}, square_width, square_width};

    Rectangle r6{Point{200, 300}, square_width, square_width};
    r6.set_fill_color(Color::red);

    Rectangle r7{Point{100, 300}, square_width, square_width};

    Rectangle r8{Point{100, 200}, square_width, square_width};
    r8.set_fill_color(Color::red);

    win.attach(r1);
    win.attach(r2);
    win.attach(r3);
    win.attach(r4);
    win.attach(r5);
    win.attach(r6);
    win.attach(r7);
    win.attach(r8);

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
