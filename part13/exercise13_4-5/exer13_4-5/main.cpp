// Exercise 13_4_5
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------


void test(const Rectangle& r, string& res)
{
    ostringstream ss;
    ss << "nw: " << nw(r).x << ','
       << nw(r).y << "; " ;
    ss << "n: " << n(r).x << ','
       << n(r).y << "; " ;
    ss << "s: " << s(r).x << ','
       << s(r).y << "; " ;
    ss << "e: " << e(r).x << ','
       << e(r).y << "; " ;
    ss << "w: " << w(r).x << ','
       << w(r).y << "; " ;
    ss << "c: " << center(r).x << ','
       << center(r).y << "; " ;
    ss << "ne: " << ne(r).x << ','
       << ne(r).y << "; " ;
    ss << "se: " << se(r).x << ','
       << se(r).y << "; " ;
    ss << "sw: " << sw(r).x << ','
       << sw(r).y << "; " ;
    res = ss.str();
}

//-----------------------------------------------------------------------------

void test(const Ellipse& r, string& res)
{
    ostringstream ss;
    ss << "nw: " << nw(r).x << ','
       << nw(r).y << "; " ;
    ss << "n: " << n(r).x << ','
       << n(r).y << "; " ;
    ss << "s: " << s(r).x << ','
       << s(r).y << "; " ;
    ss << "e: " << e(r).x << ','
       << e(r).y << "; " ;
    ss << "w: " << w(r).x << ','
       << w(r).y << "; " ;
    ss << "c: " << center(r).x << ','
       << center(r).y << "; " ;
    ss << "ne: " << ne(r).x << ','
       << ne(r).y << "; " ;
    ss << "se: " << se(r).x << ','
       << se(r).y << "; " ;
    ss << "sw: " << sw(r).x << ','
       << sw(r).y << "; " ;
    res = ss.str();
}

//-----------------------------------------------------------------------------

void test(const Circle& r, string& res)
{
    ostringstream ss;
    ss << "nw: " << nw(r).x << ','
       << nw(r).y << "; " ;
    ss << "n: " << n(r).x << ','
       << n(r).y << "; " ;
    ss << "s: " << s(r).x << ','
       << s(r).y << "; " ;
    ss << "e: " << e(r).x << ','
       << e(r).y << "; " ;
    ss << "w: " << w(r).x << ','
       << w(r).y << "; " ;
    ss << "c: " << center(r).x << ','
       << center(r).y << "; " ;
    ss << "ne: " << ne(r).x << ','
       << ne(r).y << "; " ;
    ss << "se: " << se(r).x << ','
       << se(r).y << "; " ;
    ss << "sw: " << sw(r).x << ','
       << sw(r).y << "; " ;
    res = ss.str();
}

//-----------------------------------------------------------------------------

void exercise()
{
    const Point x{0, 0};
    Simple_window win{x, 1200, 800, "exer4"};
    string res;


    Rectangle rect{Point{100, 100}, 100, 50};
    test(rect, res);
    Text text_rect{Point{50, 400}, res};

    Ellipse e{Point{150, 125}, rect.width()/2, rect.height()/2};
    test(e, res);
    Text text_el{Point{50, 420}, res};

    Circle cir{Point{150, 125}, rect.height()/2};
    test(cir, res);
    Text text_cir{Point{50, 450}, res};

    Rectangle r{nw(cir), cir.radius()*2,
                cir.radius()*2};
    test(r, res);
    Text text_r{Point{50, 470}, res};

    win.attach(rect);
    win.attach(e);
    win.attach(cir);
    win.attach(r);

    win.attach(text_rect);
    win.attach(text_el);
    win.attach(text_cir);
    win.attach(text_r);
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    exercise();
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
