// exercise14_17
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void init_items(Point start, int width0, int height0,
                Vector_ref<Texted_box>& vr)
{
    /*static const vector<string> labels = {

                  ,        ,
        ,    ,
        ,     ,    ,
        ,         "future_error",    "range_error",
        "overflow_error",       "underflow_error", "system_error",
        "bad_array_new_length", "ios_base::failure"
    };*/
    const int hy = 4 * height0;
    constexpr int xborder = 10;

    double dx = 1200.00/8.00;
    int dw = -39;
    vr.push_back(new Texted_box {start, width0 + dw, height0, "exception"});
    dw = -32;
    vr.push_back(new Texted_box {Point{xborder, height0 + hy},
                                 width0+dw, height0, "logic_error"});
    dw = -15;
    vr.push_back(new Texted_box {Point{vr[vr.size()-1].point(0).x + dx, height0 + hy},
                                 width0 + dw, height0, "runtime_error"});
    dw = -30;
    vr.push_back(new Texted_box {Point{vr[vr.size()-1].point(0).x + dx, height0 + hy},
                                 width0 + dw, height0, "bad_typeid"});
    dw = -38;
    vr.push_back(new Texted_box {Point{vr[vr.size()-1].point(0).x + dx, height0 + hy},
                                 width0 + dw, height0, "bad_cast"});
    dw = -10;
    vr.push_back(new Texted_box {Point{vr[vr.size()-1].point(0).x + dx, height0 + hy},
                                 width0 + dw, height0, "bad_weak_ptr"});
    dw = 12;
    vr.push_back(new Texted_box {Point{vr[vr.size()-1].point(0).x + dx, height0 + hy},
                                 width0 + dw, height0, "bad_function_call"});
    dw = -38;
    vr.push_back(new Texted_box {Point{vr[vr.size()-1].point(0).x + dx, height0 + hy},
                                 width0 + dw, height0, "bad_alloc"});
    dw = -9;
    vr.push_back(new Texted_box {Point{vr[vr.size()-1].point(0).x + dx, height0 + hy},
                                 width0 + dw, height0, "bad_exception"});
    dw = 10;
    vr.push_back(new Texted_box {Point{xborder*4, height0 + hy + hy/3},
                                 width0 + dw, height0, "invalid_argument"});
    dw = -13;
    vr.push_back(new Texted_box {Point{vr[vr.size()-1].point(0).x,
                                       vr[vr.size()-1].point(0).y + hy/3},
                                 width0 + dw, height0, "domain_error"});
    dw = -13;
    vr.push_back(new Texted_box {Point{vr[vr.size()-1].point(0).x,
                                       vr[vr.size()-1].point(0).y + hy/3},
                                 width0 + dw, height0, "length_error"});
    dw = -13;
    vr.push_back(new Texted_box {Point{vr[vr.size()-1].point(0).x,
                                       vr[vr.size()-1].point(0).y + hy/3},
                                 width0 + dw, height0, "out_of_range"});
    dw = -13;
    vr.push_back(new Texted_box {Point{vr[vr.size()-1].point(0).x,
                                       vr[vr.size()-1].point(0).y + hy/3},
                                 width0 + dw, height0, "future_error"});

}

//-----------------------------------------------------------------------------

void exercise14_17()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 14_17"};

    const int width0 = win.x_max()/10;
    const int height0 = win.y_max()/20;

    Point start{win.x_max()/2-width0,win.y_max()/10};
    Vector_ref<Texted_box> items;
    init_items(start, width0, height0, items);

    for (int i=0; i < items.size(); ++i)
        win.attach(items[i]);

    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    exercise14_17();
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
