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
    Simple_window win{t1, x_max(), y_max(), "Canvas"};

    const int rect_width = x_max() * 2.0/3;
    const int rect_height = y_max() * 3.0/4;

    const double cm_per_inch = 2.57;
    float ver_dpi = 0.00;
    float hor_dpi = 0.00;
    Fl::screen_dpi(hor_dpi, ver_dpi);
    const double screen_dpi = (hor_dpi + ver_dpi) / 2;
    const double dot_per_cm = screen_dpi / cm_per_inch;
    int rect_line_with = dot_per_cm / 2;

    Rectangle r{Point{50, 50}, rect_width, rect_height};
    r.set_style(Line_style(Line_style::solid, rect_line_with));

    ostringstream oss;
    oss << "screen size: " << x_max() << "*" << y_max()
        << "; window size: " << win.x_max() << "*" << win.y_max()
        << "; screen_dpi: " << screen_dpi;
    Text sizes{Point{100, 20}, oss.str()};

    win.attach(r);
    win.attach(sizes);
    win.set_label("Canvas");
    win.wait_for_button();
    std::cout << "y_max = " << win.y_max();
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
