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
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 13_10"};

    Right_triangle rt1{Point{300, 300}, 300, 150};
    Right_triangle rt2{Point{rt1.top().x + rt1.cathetus1(),
                       rt1.top().y + rt1.cathetus2()},
                       -rt1.cathetus1(), -rt1.cathetus2()};
    Right_triangle rt3{Point{rt1.top().x + rt1.cathetus1()/3,
                       rt1.top().y},
                       -rt1.cathetus1()/3, -rt1.cathetus2()/2};
    Right_triangle rt4{Point{rt2.top().x - rt1.cathetus1()/3,
                       rt1.top().y},
                       rt1.cathetus1()/3, -rt1.cathetus2()/2};

    Right_triangle rt5{Point{rt3.top().x,
                       rt1.top().y + rt1.cathetus2()},
                       rt3.cathetus1(), -rt3.cathetus2()};

    Right_triangle rt6{Point{rt4.top().x,
                       rt1.top().y + rt1.cathetus2()},
                       rt4.cathetus1(), -rt4.cathetus2()};

    Right_triangle rt7{rt5.top(), rt6.top().x - rt5.top().x,
                      rt5.cathetus2()};

    Right_triangle rt8{Point{rt6.top().x, rt6.top().y+rt6.cathetus2()},
                       -(rt6.top().x - rt5.top().x),-rt5.cathetus2()};

    Right_triangle rt9{rt3.top(),-rt3.cathetus1(),
                       rt3.cathetus2()};

    Right_triangle rt10{Point{rt4.top().x,rt4.top().y+rt4.cathetus2()},
                       -(rt4.top().x - rt3.top().x), -rt4.cathetus2()};


    win.attach(rt1);
    win.attach(rt2);
    win.attach(rt3);
    win.attach(rt4);
    win.attach(rt5);
    win.attach(rt6);
    win.attach(rt7);
    win.attach(rt8);
    win.attach(rt9);
    win.attach(rt10);

    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    exercise13_14();
    //exercise13_15();
    //exercise13_16();
    //exercise13_17();
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
