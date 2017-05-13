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

    Line fist_ch_line1{Point{200, 375}, Point{200, 225}};
    Line fist_ch_line2{Point{200, 375}, Point{250, 375}};
    Line fist_ch_line3{Point{200, 300}, Point{250, 300}};
    Line fist_ch_line4{Point{200, 225}, Point{250, 225}};

    fist_ch_line1.set_color(Color::red);
    fist_ch_line2.set_color(Color::red);
    fist_ch_line3.set_color(Color::red);
    fist_ch_line4.set_color(Color::red);

    fist_ch_line1.set_style(Line_style(Line_style::solid, 5));
    fist_ch_line2.set_style(Line_style(Line_style::solid, 5));
    fist_ch_line3.set_style(Line_style(Line_style::solid, 5));
    fist_ch_line4.set_style(Line_style(Line_style::solid, 5));

    Line second_ch_line1{Point{350, 365}, Point{350, 235}};
    Line second_ch_line2{Point{360, 375}, Point{400, 375}};
    Line second_ch_line3{Point{350, 235}, Point{360, 225}};
    Line second_ch_line4{Point{360, 225}, Point{400, 225}};
    Line second_ch_line5{Point{350, 365}, Point{360, 375}};

    second_ch_line1.set_color(Color::blue);
    second_ch_line2.set_color(Color::blue);
    second_ch_line3.set_color(Color::blue);
    second_ch_line4.set_color(Color::blue);
    second_ch_line5.set_color(Color::blue);

    second_ch_line1.set_style(Line_style(Line_style::solid, 5));
    second_ch_line2.set_style(Line_style(Line_style::solid, 5));
    second_ch_line3.set_style(Line_style(Line_style::solid, 5));
    second_ch_line4.set_style(Line_style(Line_style::solid, 5));
    second_ch_line5.set_style(Line_style(Line_style::solid, 5));

    win.attach(fist_ch_line1);
    win.attach(fist_ch_line2);
    win.attach(fist_ch_line3);
    win.attach(fist_ch_line4);

    win.attach(second_ch_line1);
    win.attach(second_ch_line2);
    win.attach(second_ch_line3);
    win.attach(second_ch_line4);
    win.attach(second_ch_line5);

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

