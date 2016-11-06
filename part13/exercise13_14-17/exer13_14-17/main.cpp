// exercise13_14-17
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void exercise13_14()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 13_14"};
    Vector_ref <Right_triangle> vr;
    Right_triangle rt1{Point{300, 300}, 300, 150};
    vr.push_back(rt1);
    Right_triangle rt2{Point{rt1.top().x + rt1.cathetus1(),
                       rt1.top().y + rt1.cathetus2()},
                       -rt1.cathetus1(), -rt1.cathetus2()};
    vr.push_back(rt2);
    Right_triangle rt3{Point{rt1.top().x + rt1.cathetus1()/3,
                       rt1.top().y},
                       -rt1.cathetus1()/3, -rt1.cathetus2()/2};
    vr.push_back(rt3);
    Right_triangle rt4{Point{rt2.top().x - rt1.cathetus1()/3,
                       rt1.top().y},
                       rt1.cathetus1()/3, -rt1.cathetus2()/2};
    vr.push_back(rt4);
    Right_triangle rt5{Point{rt3.top().x,
                       rt1.top().y + rt1.cathetus2()},
                       rt3.cathetus1(), -rt3.cathetus2()};
    vr.push_back(rt5);
    Right_triangle rt6{Point{rt4.top().x,
                       rt1.top().y + rt1.cathetus2()},
                       rt4.cathetus1(), -rt4.cathetus2()};
    vr.push_back(rt6);
    Right_triangle rt7{rt5.top(), rt6.top().x - rt5.top().x,
                      rt5.cathetus2()};
    vr.push_back(rt7);
    Right_triangle rt8{Point{rt6.top().x, rt6.top().y+rt6.cathetus2()},
                       -(rt6.top().x - rt5.top().x),-rt5.cathetus2()};
    vr.push_back(rt8);
    Right_triangle rt9{rt3.top(),-rt3.cathetus1(),
                       rt3.cathetus2()};
    vr.push_back(rt9);
    Right_triangle rt10{Point{rt4.top().x,rt4.top().y+rt4.cathetus2()},
                       -(rt4.top().x - rt3.top().x), -rt4.cathetus2()};
    vr.push_back(rt10);

    for (int i=0; i < vr.size(); ++i) {
        vr[i].set_fill_color(i*2);
        win.attach(vr[i]);
    }
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

void exercise13_15()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 13_15"};
    int h = 20;
    int w = 50;
    Vector_ref<Right_triangle> vr;
    for (int i=0; i < win.x_max()/w; ++i)
        for (int j=0; j < win.y_max()/h; ++j) {
            vr.push_back(new Right_triangle{Point{i*w, j*h}, w, h});
            vr[vr.size()-1].set_fill_color(Color::black);
            win.attach(vr[vr.size()-1]);
            vr.push_back(new Right_triangle{Point{i*w+w, j*h+h}, -w, -h});
            vr[vr.size()-1].set_fill_color(Color::white);
            win.attach(vr[vr.size()-1]);
        }
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

void exercise13_16_17()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 13_16"};
    int h = 30;
    int w = 30;
    int even_h = -6;
    int odd_h = -3;
    Vector_ref<Regular_hexagon> vr;
    for (int i=0; i < win.x_max()/w; ++i)
        for (int j=0; j < win.y_max()/h; ++j) {
            if(j==0) {
                vr.push_back(new Regular_hexagon{Point{3*i*w+w,h}, w});
                vr[vr.size()-1].set_fill_color(Color{i*16+j});
                win.attach(vr[vr.size()-1]);
            }
            else if (j%2 == 0) {
                vr.push_back(new Regular_hexagon{
                                 Point{3*i*w+w,
                                       vr[vr.size()-1].center().y+h+even_h},
                                 w});
                vr[vr.size()-1].set_fill_color(Color{i*4+j});
                win.attach(vr[vr.size()-1]);
            }
            else {
                vr.push_back(new Regular_hexagon{
                                 Point{vr[vr.size()-1].center().x+1.5*w,
                                       vr[vr.size()-1].center().y+h+odd_h}, w});
                vr[vr.size()-1].set_fill_color(Color{i*4+j});
                win.attach(vr[vr.size()-1]);
            }
        }
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    //exercise13_14();
    //exercise13_15();
    exercise13_16_17();

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
