// exercise14_17
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void init_exeption_items(Simple_window& win,
                         Vector_ref<Texted_box>& vr)
{
    const int height0 = win.y_max()/20;
    const int hy = 4 * height0;
    constexpr int xborder = 10;

    static const vector<string> exception_labels = {
        "logic_error", "bad_typeid",   "runtime_error",
        "bad_cast",    "bad_weak_ptr", "bad_function_call",
        "bad_alloc",   "bad_exception"
    };
    const double dx = win.x_max() * 1.00 / exception_labels.size();
    for (int i=0; i < exception_labels.size(); ++i)
        if (i == 0)
            vr.push_back(new Texted_box {
                                Point{xborder, height0 + hy},
                                exception_labels[i]
                         });
        else
            vr.push_back(new Texted_box {
                                Point{vr[vr.size()-1].point(0).x + dx,
                                      vr[vr.size()-1].point(0).y},
                                exception_labels[i]
                         });
    for (int i =0; i < vr.size(); ++i)
        win.attach(vr[i]);
}

//-----------------------------------------------------------------------------

void init_logic_items(Simple_window& win,
                      Vector_ref<Texted_box>& vr)
{
    const int height0 = win.y_max()/20;
    const int hy = 4 * height0;
    constexpr int xborder = 40;
    static const vector<string> logic_labels = {
        "invalid_argument", "domain_error",
        "length_error",     "out_of_range",
        "future_error"
    };
    for (int i=0; i < logic_labels.size(); ++i)
        if (i == 0)
            vr.push_back(new Texted_box {
                                Point{xborder, height0 + hy + hy/3},
                                logic_labels[i]
                         });
        else
            vr.push_back(new Texted_box {
                                Point{xborder, vr[vr.size()-1].point(0).y + hy/3},
                                logic_labels[i]
                         });
    for (int i =0; i < vr.size(); ++i)
        win.attach(vr[i]);
}

//-----------------------------------------------------------------------------

void init_runtime_items(int width0, int height0,
                        Vector_ref<Texted_box>& vr)
{
    /*static const vector<string> labels = {

                  ,        ,
        ,    ,
        ,     ,    ,
        ,         ,    ,
        ,       , ,
        "bad_array_new_length", "ios_base::failure"
    };*/
    const int hy = 4 * height0;
    constexpr int xborder = 220;
    int dw = -20;
    vr.push_back(new Texted_box {Point{xborder, height0 + hy + hy/3},
                                 width0 + dw, height0, "range_error"});
    dw = -2;
    vr.push_back(new Texted_box {Point{vr[vr.size()-1].point(0).x,
                                       vr[vr.size()-1].point(0).y + hy/3},
                                 width0 + dw, height0, "overflow_error"});
    dw = 5;
    vr.push_back(new Texted_box {Point{vr[vr.size()-1].point(0).x,
                                       vr[vr.size()-1].point(0).y + hy/3},
                                 width0 + dw, height0, "underflow_error"});
    dw = -13;
    vr.push_back(new Texted_box {Point{vr[vr.size()-1].point(0).x,
                                       vr[vr.size()-1].point(0).y + hy/3},
                                 width0 + dw, height0, "system_error"});

}

//-----------------------------------------------------------------------------

void exercise14_17()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 14_17"};

    const int width0 = win.x_max()/10;
    const int height0 = win.y_max()/20;

    Point start{win.x_max()/2-width0,win.y_max()/10};
    Vector_ref<Texted_box> exeption_items;
    exeption_items.push_back(new Texted_box {start, "exception"});
    init_exeption_items(win, exeption_items);

    Vector_ref<Texted_box> logic_items;
    init_logic_items(win, logic_items);

    Vector_ref<Texted_box> runtime_items;
    init_runtime_items(width0, height0, runtime_items);

    for (int i=0; i < exeption_items.size(); ++i)
        win.attach(exeption_items[i]);
    for (int i =0; i < runtime_items.size(); ++i)
        win.attach(runtime_items[i]);


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
