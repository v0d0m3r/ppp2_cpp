//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "Func_window.hpp"

//-----------------------------------------------------------------------------

using namespace Graph_lib;

//-----------------------------------------------------------------------------

int func_graph()
{
    constexpr int xmax = 600;      // Размер окна
    constexpr int ymax = 600;

    constexpr int x_orig = xmax/2; // Центр окна (0, 0)
    constexpr int y_orig = ymax/2;
    const Point orig{x_orig, y_orig};

    constexpr int r_min = -3;      // Диапазон
    constexpr int r_max = 3;

    constexpr int n_points = 400;  // Количество точек в диапазоне

    constexpr int x_scale = 50;    // Масштабные множетели
    constexpr int y_scale = 50;

    constexpr int xoffset = 50;    //  от левого края до оси у
    constexpr int yoffset = 50;    //  от нижнего края до оси х

    constexpr int xspace = 50;     // Пространство за осями
    constexpr int yspace = 50;
                                   // Длины осей
    constexpr int xlength = xmax - xoffset - xspace;
    constexpr int ylength = ymax - yoffset - yspace;

    Axis x{Axis::x, Point{xoffset, y_orig},
           xlength, xlength/x_scale, "one notch = 1"};
    Axis y{Axis::y, Point{x_orig, ylength+yspace},
           ylength, ylength/y_scale, "one notch = 1"};
    x.set_color(Color::red);
    y.set_color(Color::red);

    Funct f{sin, r_min, r_max, orig, n_points, x_scale, y_scale};
    f.set_color(Color::blue);

    Func_window cw{Point{100, 100}, xmax, ymax, "Func_window", f};
    cw.attach(x);
    cw.attach(y);
    return gui_main();
}

//-----------------------------------------------------------------------------

int main()
try {
    return func_graph();
}
catch(exception& e) {
    cerr << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "exiting\n";
    return -2;
}

//-----------------------------------------------------------------------------
