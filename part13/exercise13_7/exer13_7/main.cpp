/*
Exercise 13_7
Рисуем диаграмму цветов rgb, ввиде трех
пересекающихся кругов, места пересечения
образуют цвета:
magenta, cyan, yellow, white.
Также используется контур сглаживания для
мест пересечения главных углов толщина линии 3.
TODO: убрать контур для сглаживания.
*/
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
    Simple_window win{x, 1200, 800, "exercise 13_7"};

    const Point rd_cntr{200, 200};
    const Point grn_cntr{300, 200};
    const Point bl_cntr{250, 300};

    constexpr int radius = 100;
    // Три основных груга
    Circle cir_red{rd_cntr, radius};
    cir_red.set_fill_color(Color::red);
    cir_red.set_color(Color::invisible);

    Circle cir_green{grn_cntr, radius};
    cir_green.set_fill_color(Color::green);
    cir_green.set_color(Color::invisible);

    Circle cir_blue{bl_cntr, radius};
    cir_blue.set_fill_color(Color::blue);
    cir_blue.set_color(Color::invisible);
    // Рисуем места пересечения, в виде секторов
    int delta = 13; // Разница между центром круга
                    // и центром сектора
    Arc red_magenta{Point{rd_cntr.x, rd_cntr.y+delta},
                    radius, radius-delta-1};
    red_magenta.set_fill_color(Color::magenta);
    red_magenta.set_color(Color::invisible);
    red_magenta.set_begin_angle(240);
    red_magenta.set_end_angle(300);

    delta = 5;
    Arc green_white{Point{grn_cntr.x, grn_cntr.y+delta},
                    radius, radius-delta};
    green_white.set_fill_color(Color::white);   // Заполняем дугу цветом
                                                // получается сектор
    green_white.set_color(Color::invisible);
    green_white.set_begin_angle(180);
    green_white.set_end_angle(240);

    delta = 8;
    Arc red_white{Point{rd_cntr.x, rd_cntr.y+delta},
                  radius, radius-delta};
    red_white.set_fill_color(Color::white);
    red_white.set_color(Color::invisible);
    red_white.set_begin_angle(300);
    red_white.set_end_angle(360);

    delta = 11;
    Arc blue_white{Point{bl_cntr.x, bl_cntr.y-delta},
                   radius, radius-delta};
    blue_white.set_fill_color(Color::white);
    blue_white.set_color(Color::invisible);
    blue_white.set_begin_angle(60);
    blue_white.set_end_angle(120);

    delta = 12;
    Arc blue_magenta{Point{bl_cntr.x+2, bl_cntr.y-delta},
                     radius, radius-delta-2};
    blue_magenta.set_fill_color(Color::magenta);
    blue_magenta.set_color(Color::invisible);
    blue_magenta.set_begin_angle(120);
    blue_magenta.set_end_angle(177);

    Arc blue_cyan{Point{bl_cntr.x-2, bl_cntr.y-delta},
                  radius, radius-delta-2};
    blue_cyan.set_fill_color(Color::cyan);
    blue_cyan.set_color(Color::invisible);
    blue_cyan.set_begin_angle(2);
    blue_cyan.set_end_angle(60);

    delta = 0;
    Arc red_yellow{Point{rd_cntr.x, rd_cntr.y+delta},
                   radius, radius-delta};
    red_yellow.set_fill_color(Color::yellow);
    red_yellow.set_color(Color::invisible);
    red_yellow.set_begin_angle(-10);
    red_yellow.set_end_angle(60);

    Arc green_yellow{Point{grn_cntr.x, grn_cntr.y+delta},
                     radius, radius-delta};
    green_yellow.set_fill_color(Color::yellow);
    green_yellow.set_color(Color::invisible);
    green_yellow.set_begin_angle(120);
    green_yellow.set_end_angle(190);

    delta = 13;
    Arc green_cyan{Point{grn_cntr.x, grn_cntr.y+delta},
                   radius, radius-delta-1};
    green_cyan.set_fill_color(Color::cyan);
    green_cyan.set_color(Color::invisible);
    green_cyan.set_begin_angle(240);
    green_cyan.set_end_angle(300);
    // Для простоты рисуем контуры, чтобы сгладить
    // неточности построения секторов
    Arc arc_red{rd_cntr, radius, radius};
    arc_red.set_style(Line_style{Line_style::solid, 3});
    Arc arc_green{grn_cntr, radius, radius};
    arc_green.set_style(Line_style{Line_style::solid, 3});
    Arc arc_blue{bl_cntr, radius, radius};
    arc_blue.set_style(Line_style{Line_style::solid, 3});

    win.attach(cir_blue);
    win.attach(cir_red);
    win.attach(cir_green);

    win.attach(red_magenta);
    win.attach(green_cyan);
    win.attach(blue_cyan);
    win.attach(red_white);
    win.attach(blue_magenta);
    win.attach(green_white);
    win.attach(red_yellow);
    win.attach(green_yellow);
    win.attach(blue_white);

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
