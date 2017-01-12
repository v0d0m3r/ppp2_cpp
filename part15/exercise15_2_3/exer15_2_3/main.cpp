//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

double fac(int n)          // n! Факториал
{
    double r = 1;
    while (n > 1) {
        r *= n;
        --n;
    }
    return r;
}

//-----------------------------------------------------------------------------

double term(double x, int n)    // n-й член ряда
{
    return pow(x, n) / fac(n);
}

//-----------------------------------------------------------------------------

double expe(double x, int n)
{
    double sum = 0;
    for (int i=0; i < n; ++i) sum += term(x, i);
    return sum;
}

//-----------------------------------------------------------------------------

void exercise15_2_3()
{
    constexpr int xmax = 600;       // Размер окна
    constexpr int ymax = 400;

    constexpr int x_orig = xmax/2;  // Центр окна (0, 0)
    constexpr int y_orig = ymax/2;
    const Point orig{x_orig, y_orig};

    constexpr int r_min = -10;      // Диапазон {-10, 7)
    constexpr int r_max = 7;

    constexpr int n_points = 100;   // Количество точек в диапазоне

    constexpr int x_scale = 40;     // Масштабные множетели
    constexpr int y_scale = 40;

    constexpr int xlength = xmax - 40;  // Оси чуть меньше окна
    constexpr int ylength = ymax - 40;

    Simple_window win{Point{100, 100}, xmax, ymax, "Exercise15_2_3"};

    Axis x{Axis::x, Point{20, y_orig},
           xlength, xlength/x_scale, "one notch = 1"};
    Axis y{Axis::y, Point{x_orig, ylength+20},
           ylength, ylength/y_scale, "one notch = 1"};
    x.set_color(Color::red);
    y.set_color(Color::red);

    win.attach(x);
    win.attach(y);

    win.wait_for_button();


    Funct real_exp{exp, r_min, r_max, orig, n_points, x_scale, y_scale};
    real_exp.set_color(Color::cyan);

    win.attach(real_exp);

    Funct_precision real_exp1{exp, r_min, r_max, orig, n_points, x_scale, y_scale, 0.0001};
    real_exp1.set_color(Color::yellow);

    win.attach(real_exp1);
    win.wait_for_button();


    Funct tf{exp, r_min, r_max, orig, n_points, x_scale, y_scale};

    tf.set_color(Color::blue);
    win.attach(tf);
    win.wait_for_button();
    tf.set_function_capture([](double x)
                            { return sin(x); });
    tf.set_r_min(-20);
    win.wait_for_button();

    tf.set_orig(Point{xmax/4, ymax/2});
    y.move(tf.point(0).x - y.point(0).x, 0);

    tf.set_r_max(19);

    tf.set_xscale(10);
    tf.set_yscale(40);

    tf.set_color(Color::dark_green);

    tf.set_function(cos);
    win.wait_for_button();

    for (int n=0; n < 2; ++n) {
        // Очередное приближение:
        tf.set_function_capture([n] (double x) { return expe(x, n); });
        win.wait_for_button();
    }

    cout << "r_min          - " << tf.r_min() << '\n'
         << "r_max          - " << tf.r_max() << '\n'
         << "orig           - " << tf.orig().x << ", "<< tf.orig().y << '\n'
         << "count_of_point - " << tf.count_of_points() << '\n'
         << "xscale         - " << tf.xscale() << '\n'
         << "yscale         - " << tf.yscale() << '\n';
}

//-----------------------------------------------------------------------------

int main()
try {
    exercise15_2_3();
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
