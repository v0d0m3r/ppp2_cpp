//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

double term(int n)
{
    return pow(-1, n) / (2*n + 1);
}

//-----------------------------------------------------------------------------

double leibniz(int n)
{
    double sum = 0.00;
    for (int i=0; i < n; ++i)   sum += term(i);
    return sum;
}

//-----------------------------------------------------------------------------

void execise15_5()
{
    cout << "n = 1: "      << leibniz(1)      << '\n'
         << "n = 10: "     << leibniz(10)     << '\n'
         << "n = 100: "    << leibniz(100)    << '\n'
         << "n = 1000: "   << leibniz(1000)   << '\n'
         << "n = 10000: "  << leibniz(10000)  << '\n'
         << "n = 100000: " << leibniz(100000) << '\n';
}

//-----------------------------------------------------------------------------

void exercise15_4()
{
    constexpr int xmax = 600;       // Размер окна
    constexpr int ymax = 400;

    constexpr int x_orig = xmax/2;  // Центр окна (0, 0)
    constexpr int y_orig = ymax/2;
    const Point orig{x_orig, y_orig};

    constexpr int r_min = -10;      // Диапазон {-10, 7)
    constexpr int r_max = 7;

    constexpr int n_points = 400;   // Количество точек в диапазоне

    constexpr int x_scale = 100;    // Масштабные множетели
    constexpr int y_scale = 100;

    constexpr double precision = 0.1;

    constexpr int xlength = xmax - 40;  // Оси чуть меньше окна
    constexpr int ylength = ymax - 40;

    Simple_window win{Point{100, 100}, xmax, ymax, "Exercise15_4"};

    Axis x{Axis::x, Point{20, y_orig},
           xlength, xlength/x_scale, "one notch = 1"};
    Axis y{Axis::y, Point{x_orig, ylength+20},
           ylength, ylength/y_scale, "one notch = 1"};
    x.set_color(Color::red);
    y.set_color(Color::red);

    win.attach(x);
    win.attach(y);

    win.wait_for_button();

    Funct f{sin, r_min, r_max, orig, n_points,
             x_scale, y_scale, precision};
    f.set_color(Color::blue);
    Funct f2{cos, r_min, r_max, orig, n_points,
             x_scale, y_scale, precision};
    f2.set_color(Color::dark_green);
    win.attach(f);
    win.attach(f2);

    Text ts{Point{20, y_orig+25}, "sin(x)"};
    Text ts2{Point{5, y_orig+80}, "cos(x)"};
    win.attach(ts);
    win.attach(ts2);

    Funct f3{Fct_capture([](double x) { return sin(x) + cos(x); }),
             r_min, r_max, orig, n_points, x_scale, y_scale, precision};
    f3.set_color(Color::yellow);

    Funct f4{Fct_capture([](double x) { return sin(x)*sin(x) + cos(x)*cos(x); }),
             r_min, r_max, orig, n_points, x_scale, y_scale, precision};
    f4.set_color(Color::dark_magenta);

    win.attach(f3);
    win.attach(f4);

    Text ts3{Point{20, y_orig+120}, "sin(x) + cos(x)"};
    Text ts4{Point{20, y_orig-105}, "sin(x)*sin(x) + cos(x)*cos(x)"};

    win.attach(ts3);
    win.attach(ts4);
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    //exercise15_4();
    execise15_5();
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
