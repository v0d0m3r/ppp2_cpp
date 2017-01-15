//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void exercise15_6()
{
    constexpr int xmax = 600;       // Размер окна
    constexpr int ymax = 600;

    constexpr int x_orig = 20;      // Начало координат(0, 0)
    constexpr int y_orig = ymax-40;
    const Point orig{x_orig, y_orig};

    constexpr int x_scale = 40;     // Масштабные множетели
    constexpr int y_scale = 40;

    constexpr int xlength = xmax - 40;  // Оси чуть меньше окна
    constexpr int ylength = ymax - 60;

    Simple_window win{Point{100, 100}, xmax, ymax, "Exercise15_6"};

    Axis x{Axis::x, Point{20, y_orig},
           xlength, xlength/x_scale, "one notch = 1"};
    Axis y{Axis::y, Point{x_orig, ylength+20},
           ylength, ylength/y_scale, "one notch = 1"};
    x.set_color(Color::red);
    y.set_color(Color::red);

    win.attach(x);
    win.attach(y);
    win.wait_for_button();

    constexpr double w = 1.00;
    constexpr double h = 1.00;

    Column_chart cc{orig, w, h, x_scale, y_scale};
    win.attach(cc);
    win.wait_for_button();

    constexpr double h2 = 2.00;
    constexpr double h3 = 3.00;
    constexpr double h4 = 4.00;

    cc.add(h2);
    cc.add(h3);
    cc.add(h4);
    cc.add(h3);
    cc.add(h2);
    cc.add(h3);
    cc.add(h4);

    win.wait_for_button();
}

//-----------------------------------------------------------------------------

void exercise15_7()
{
    constexpr int xmax = 600;       // Размер окна
    constexpr int ymax = 600;

    constexpr int x_orig = 20;      // Начало координат(0, 0)
    constexpr int y_orig = ymax-40;
    const Point orig{x_orig, y_orig};

    constexpr int x_scale = 40;     // Масштабные множетели
    constexpr int y_scale = 40;

    constexpr int xlength = xmax - 40;  // Оси чуть меньше окна
    constexpr int ylength = ymax - 60;

    Simple_window win{Point{100, 100}, xmax, ymax, "Exercise15_7"};

    Axis x{Axis::x, Point{20, y_orig},
           xlength, xlength/x_scale, "one notch = 1"};
    Axis y{Axis::y, Point{x_orig, ylength+20},
           ylength, ylength/y_scale, "one notch = 1"};
    x.set_color(Color::red);
    y.set_color(Color::red);

    win.attach(x);
    win.attach(y);
    win.wait_for_button();

    constexpr double w = 1.00;
    constexpr double h = 1.00;

    Marked_column_chart cc{orig, w, h, "Hello world" ,x_scale, y_scale};
    cc.mark(0).move(100, 100);
    win.attach(cc);
    win.wait_for_button();

    constexpr double h2 = 2.00;
    constexpr double h3 = 3.00;
    constexpr double h4 = 4.00;

    cc.add(h2);
    cc.add(h3);
    cc.add(h4);
    cc.add(h3);
    cc.add(h2);
    cc.add(h3);
    cc.add(h4);

    cc.add_mark("55%");
    cc.mark(cc.number_of_marks()-1).move(300, 300);

    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    exercise15_7();
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
