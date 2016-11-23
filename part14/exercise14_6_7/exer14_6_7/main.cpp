// exercise14_6_7
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void exercise14_6()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 14_6"};
    Striped_circle sc{Point{400, 400}, 300};
    sc.set_fill_color(Color::blue);
    sc.set_style(Line_style(Line_style::solid, 5));
    win.attach(sc);
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

void exercise14_7()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 14_7"};
    Striped_closed_polyline scp;
    scp.add(Point{200, 100});
    scp.add(Point{200, 200});
    scp.add(Point{150, 150});
    scp.add(Point{150, 300});
    scp.add(Point{200, 250});
    scp.add(Point{200, 350});
    scp.add(Point{250, 350});
    scp.add(Point{250, 250});

    scp.add(Point{300, 300});
    scp.add(Point{300, 150});
    scp.add(Point{250, 200});
    scp.add(Point{250, 100});
    scp.set_fill_color(Color::magenta);
    scp.set_style(Line_style(Line_style::solid, 3));
    scp.move(0, 250);

    Striped_closed_polyline scp2;
    scp2.set_fill_color(Color::blue);

    scp2.add(Point{400, 400});
    scp2.add(Point{400, 500});
    scp2.add(Point{500, 500});
    scp2.add(Point{500, 400});
    scp2.add(Point{550, 400});
    scp2.add(Point{550, 500});
    scp2.move(0, -250);
    scp2.set_style(Line_style(Line_style::solid, 3));


    Striped_closed_polyline scp3;
    scp3.set_fill_color(Color::cyan);
    for (int i = 100; i < 700; i+=50)
        if (i%100)
            scp3.add(Point{i, i+50});
        else
            scp3.add(Point{i, i-50});

    scp3.set_style(Line_style(Line_style::solid, 3));

    win.attach(scp);
    win.attach(scp2);
    win.attach(scp3);

    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {

    //exercise14_6();
    exercise14_7();
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
