// Exercise 13_4_5
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

Point nw(const Rectangle& r)
{
    return r.point(0);
}

//-----------------------------------------------------------------------------

Point nw(const Ellipse& el)
{
    return nw(Rectangle{el.point(0), 2*el.major(), 2*el.minor()});
}

//-----------------------------------------------------------------------------

Point nw(const Circle& cir)
{
    return nw(Rectangle{cir.point(0), 2*cir.radius(),
                        2*cir.radius()});
}

//-----------------------------------------------------------------------------

Point n(const Rectangle& r)
{
    return Point{nw(r).x, nw(r).y+r.height()/2};
}

//-----------------------------------------------------------------------------

Point n(const Ellipse& el)
{
    return n(Rectangle{el.point(0), 2*el.major(), 2*el.minor()});
}

//-----------------------------------------------------------------------------

Point n(const Circle& cir)
{
    return n(Rectangle{cir.point(0), 2*cir.radius(),
                       2*cir.radius()});
}

//-----------------------------------------------------------------------------

Point s(const Rectangle& r)
{
    return Point{n(r).x+r.width(), n(r).y};
}

//-----------------------------------------------------------------------------

Point s(const Ellipse& el)
{
    return s(Rectangle{el.point(0), 2*el.major(), 2*el.minor()});
}

//-----------------------------------------------------------------------------

Point s(const Circle& cir)
{
    return s(Rectangle{cir.point(0), 2*cir.radius(),
                       2*cir.radius()});
}

//-----------------------------------------------------------------------------

Point e(const Rectangle& r)
{
    return Point{nw(r).x+r.width()/2, nw(r).y+r.height()};
}

//-----------------------------------------------------------------------------

Point e(const Ellipse& el)
{
    return e(Rectangle{el.point(0), 2*el.major(), 2*el.minor()});
}

//-----------------------------------------------------------------------------

Point e(const Circle& cir)
{
    return e(Rectangle{cir.point(0), 2*cir.radius(),
                       2*cir.radius()});
}

//-----------------------------------------------------------------------------

Point w(const Rectangle& r)
{
    return Point{e(r).x, nw(r).y};
}

//-----------------------------------------------------------------------------

Point w(const Ellipse& el)
{
    return w(Rectangle{el.point(0), 2*el.major(), 2*el.minor()});
}

//-----------------------------------------------------------------------------

Point w(const Circle& cir)
{
    return w(Rectangle{cir.point(0), 2*cir.radius(),
                       2*cir.radius()});
}

//-----------------------------------------------------------------------------

Point center(const Rectangle& r)
{
    return Point{w(r).x, s(r).y};
}

//-----------------------------------------------------------------------------

Point center(const Ellipse& ell)
{
    return ell.center();
}

//-----------------------------------------------------------------------------

Point center(const Circle& cir)
{
    return cir.center();
}

//-----------------------------------------------------------------------------

Point ne(const Rectangle& r)
{
    return Point{n(r).x, e(r).y};
}

//-----------------------------------------------------------------------------

Point ne(const Ellipse& el)
{
    return ne(Rectangle{el.point(0), 2*el.major(), 2*el.minor()});
}

//-----------------------------------------------------------------------------

Point ne(const Circle& cir)
{
    return ne(Rectangle{cir.point(0), 2*cir.radius(),
                        2*cir.radius()});
}

//-----------------------------------------------------------------------------

Point se(const Rectangle& r)
{
    return Point{s(r).x, e(r).y};
}

//-----------------------------------------------------------------------------

Point se(const Ellipse& el)
{
    return se(Rectangle{el.point(0), 2*el.major(), 2*el.minor()});
}

//-----------------------------------------------------------------------------

Point se(const Circle& cir)
{
    return se(Rectangle{cir.point(0), 2*cir.radius(),
                        2*cir.radius()});
}

//-----------------------------------------------------------------------------

Point sw(const Rectangle& r)
{
    return Point{s(r).x, w(r).y};
}

//-----------------------------------------------------------------------------

Point sw(const Ellipse& el)
{
    return sw(Rectangle{el.point(0), 2*el.major(),
                        2*el.minor()});
}

//-----------------------------------------------------------------------------

Point sw(const Circle& cir)
{
    return sw(Rectangle{cir.point(0), 2*cir.radius(),
                        2*cir.radius()});
}

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

void exer4()
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
    exer4();
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
