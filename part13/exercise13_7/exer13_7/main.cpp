// Exercise 13_7
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void paint_rgb_dia()
{
    const Point x{0, 0};
    Simple_window win{x, 1200, 800, "exercise 13_6"};

    Circle cir_red{Point{200, 200}, 100};
    cir_red.set_fill_color(Color::red);
    cir_red.set_color(Color::invisible);

    Circle cir_green{Point{300, 200}, 100};
    cir_green.set_fill_color(Color::green);
    cir_green.set_color(Color::invisible);

    Circle cir_blue{Point{250, 300}, 100};
    cir_blue.set_fill_color(Color::blue);
    cir_blue.set_color(Color::invisible);

    int delta = 17; // Разница между центром круга
                    // и центром сектора
    Arc red_magenta{Point{cir_red.center().x, cir_red.center().y+delta},
                    cir_red.radius(), cir_red.radius()-delta};
    red_magenta.set_fill_color(Color::magenta);
    red_magenta.set_color(Color::invisible);
    red_magenta.set_begin_angle(240);
    red_magenta.set_end_angle(300);

    delta = 10;
    Arc blue_magenta{Point{cir_blue.center().x, cir_blue.center().y-delta},
                    cir_blue.radius(), cir_blue.radius()-delta-3};
    blue_magenta.set_fill_color(Color::magenta);
    blue_magenta.set_color(Color::invisible);
    blue_magenta.set_begin_angle(120);
    blue_magenta.set_end_angle(180);


    Arc arc_red{cir_red.center(), cir_red.radius(),
                cir_red.radius()};
    arc_red.set_style(Line_style{Line_style::solid, 3});
    Arc arc_green{cir_green.center(), cir_green.radius(),
                  cir_green.radius()};
    arc_green.set_style(Line_style{Line_style::solid, 3});
    Arc arc_blue{cir_blue.center(), cir_blue.radius(),
                 cir_blue.radius()};
    arc_blue.set_style(Line_style{Line_style::solid, 3});

    win.attach(cir_red);
    win.attach(cir_green);
    win.attach(cir_blue);
    win.attach(red_magenta);
    win.attach(blue_magenta);
    win.attach(arc_green);
    win.attach(arc_blue);
    win.attach(arc_red);
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    paint_rgb_dia();
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
