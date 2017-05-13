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
    Simple_window win{t1, x_max(), y_max(), "Canvas #12_8"};

    const Point default_dot{300, 300};  // Точка отсчета
    constexpr int radius = 60;          // Радиус колец
    constexpr int delta_x = 140;        // Сдвиг по оси х
    constexpr int delta_y = 70;         // Сдвиг по оси у
    constexpr int depth = 15;           // Толщина колец
    // Верхние кольца
    Point centr_dot = default_dot;
    Circle blue_circ{centr_dot, radius};
    blue_circ.set_color(Color::blue);
    blue_circ.set_style(Line_style(Line_style::solid, depth));

    centr_dot.x += delta_x; // Сдвигаем центр для нового круга
    Circle black_circ{centr_dot, radius};
    black_circ.set_color(Color::black);
    black_circ.set_style(Line_style(Line_style::solid, depth));

    centr_dot.x += delta_x;
    Circle red_circ{centr_dot, radius};
    red_circ.set_color(Color::red);
    red_circ.set_style(Line_style(Line_style::solid, depth));
    // Нижние кольца
    centr_dot = default_dot;
    centr_dot.x += delta_x / 2;   // Только у первого нижнего окна
    centr_dot.y += delta_y;
    Circle yellow_circ{centr_dot, radius};
    yellow_circ.set_color(Color::yellow);
    yellow_circ.set_style(Line_style(Line_style::solid, depth));

    centr_dot.x += delta_x;
    Circle green_circ{centr_dot, radius};
    green_circ.set_color(Color::green);
    green_circ.set_style(Line_style(Line_style::solid, depth));

    win.attach(blue_circ);
    win.attach(black_circ);
    win.attach(red_circ);
    win.attach(yellow_circ);
    win.attach(green_circ);

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
