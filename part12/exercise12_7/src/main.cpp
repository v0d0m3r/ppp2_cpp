//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"

//-----------------------------------------------------------------------------

using namespace Graph_lib;

//-----------------------------------------------------------------------------

int main()
try {
    Point t1{0, 0};
    Simple_window win{t1, x_max(), y_max(), "Canvas"};
    int rect_x = x_max()/2 - 200;
    int rect_y = y_max()/2;
    // Рисуем центральную часть дома
    Rectangle cent_rect{Point{rect_x, rect_y}, 400, 200};
    cent_rect.set_style(Line_style(Line_style::solid, 2));
    // Крыша-чердак
    Polygon poly;
    poly.add(Point{rect_x, rect_y});
    poly.add(Point{rect_x-150, rect_y-30});
    poly.add(Point{rect_x - 75, rect_y - 150});
    poly.set_style(Line_style(Line_style::solid, 2));
    poly.set_color(Color::red);
    // Рисуем окно на чердаке
    Polygon attic_win;
    attic_win.add(Point{rect_x-30, rect_y-20});
    attic_win.add(Point{rect_x-120, rect_y-40});
    attic_win.add(Point{rect_x-75, rect_y-120});
    attic_win.set_style(Line_style(Line_style::solid, 2));
    attic_win.set_color(Color::blue);
    // Рисуем раму окна на чердаке
    // Вертикальная
    Line frame_attic_win_v{Point{rect_x-75, rect_y-120},
                          Point{rect_x-75, rect_y-30}};
    frame_attic_win_v.set_style(Line_style(Line_style::solid, 2));
    frame_attic_win_v.set_color(Color::blue);
    // Горизонтальная
    Line frame_attic_win_h{Point{rect_x-102, rect_y-75},
                          Point{rect_x-49, rect_y-62}};
    frame_attic_win_h.set_style(Line_style(Line_style::solid, 2));
    frame_attic_win_h.set_color(Color::blue);
    // Дорисовываем боковую часть дома
    Line line1{Point{rect_x, rect_y+199}, Point{rect_x-150, rect_y+170}};
    line1.set_style(Line_style(Line_style::solid, 2));
    Line line2{Point{rect_x-150, rect_y+170}, Point{rect_x-150, rect_y-30}};
    line2.set_style(Line_style(Line_style::solid, 2));
    // Дорисовываем крышу
    Line line3{Point{rect_x-75, rect_y-150}, Point{rect_x+325, rect_y-150}};
    line3.set_style(Line_style(Line_style::solid, 2));
    Line line4{Point{rect_x+325, rect_y-150}, Point{rect_x+400, rect_y}};
    line4.set_style(Line_style(Line_style::solid, 2));
    // Рисуем трубу
    Closed_polyline pipe;
    pipe.add(Point{rect_x+180,rect_y -30});
    pipe.add(Point{rect_x+180,rect_y-200});
    pipe.add(Point{rect_x+150, rect_y-200});
    pipe.add(Point{rect_x+150, rect_y-230});
    pipe.add(Point{rect_x+280, rect_y-230});
    pipe.add(Point{rect_x+280, rect_y-200});
    pipe.add(Point{rect_x+250, rect_y-200});
    pipe.add(Point{rect_x+250, rect_y -30});
    pipe.set_style(Line_style(Line_style::solid, 2));
    pipe.set_fill_color(Color::dark_magenta);
    // Окно на центральной части
    Rectangle centr_win{Point{rect_x+150, rect_y+50}, 100, 100};
    centr_win.set_style(Line_style(Line_style::solid, 2));
    // Подоконник
    Rectangle windowsill{Point{rect_x+125, rect_y+149}, 150, 15};
    windowsill.set_style(Line_style(Line_style::solid, 2));
    windowsill.set_fill_color(Color::black);
    // Рамка горизонтальная
    Line frame_centr_win_h{Point{rect_x+150, rect_y+100},
                          Point{rect_x+250, rect_y+100}};
    frame_centr_win_h.set_style(Line_style(Line_style::solid, 2));
    frame_centr_win_h.set_color(Color::blue);
    // Вертикальная
    Line frame_centr_win_v{Point{rect_x+200, rect_y+50},
                          Point{rect_x+200, rect_y+150}};
    frame_centr_win_v.set_style(Line_style(Line_style::solid, 2));
    frame_centr_win_v.set_color(Color::blue);
    // Дверь
    Open_polyline door;
    door.add(Point{rect_x-115,rect_y+177});
    door.add(Point{rect_x-115,rect_y+70});
    door.add(Point{rect_x-65,rect_y+80});
    door.add(Point{rect_x-65, rect_y+187});
    door.set_style(Line_style(Line_style::solid, 2));
    // Дым
    Open_polyline smoke;
    smoke.add(Point{rect_x+215, rect_y-230});
    smoke.add(Point{rect_x+200, rect_y-245});
    smoke.add(Point{rect_x+240, rect_y-260});
    smoke.add(Point{rect_x+225, rect_y-275});
    smoke.add(Point{rect_x+265, rect_y-290});
    smoke.add(Point{rect_x+255, rect_y-300});
    smoke.set_style(Line_style(Line_style::solid, 2));

    win.attach(cent_rect);
    win.attach(poly);
    win.attach(attic_win);
    win.attach(frame_attic_win_v);
    win.attach(frame_attic_win_h);
    win.attach(line1);
    win.attach(line2);
    win.attach(line3);
    win.attach(line4);
    win.attach(pipe);
    win.attach(centr_win);
    win.attach(frame_centr_win_h);
    win.attach(frame_centr_win_v);
    win.attach(windowsill);
    win.attach(door);
    win.attach(smoke);

    win.set_label("Canvas #12_7");
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
    cout << "выходим\n";
    keep_window_open("~");
}
//-----------------------------------------------------------------------------
