#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void example13()
{
    using namespace Graph_lib;
    const Graph_lib::Point x{100, 100};

    Simple_window win1{x, 600, 400, "two lines"};
    Line horizontal{x, Point{200, 100}};    // Горизонтальная линия
    Line vertical{Point{150, 50},           // Вертикальная линия
                  Point{150, 150}};

    win1.attach(horizontal);                // Связываем линии с окном
    win1.attach(vertical);
    //win1.wait_for_button();                 // Вывод

    Simple_window win2{x, 600, 400, "use Lines"};
    Lines lines;
    lines.add(x, Point{200, 100});          // Горизонтальная линия
    lines.add(Point{150, 50},               // Вертикальная линия
              Point{150, 150});

    win2.attach(lines);                     // Связываем линии с окном
    //win2.wait_for_button();                 // Вывод

    Simple_window win3{x, 600, 400, "grid"};
    int x_size = win3.x_max();
    int y_size = win3.y_max();
    int x_grid = 80;
    int y_grid = 40;

    Lines grid;
    for (int x=0; x < x_size; x += x_grid)
        grid.add(Point{x, 0}, Point{x, y_size});
    for (int y=0; y < y_size; y += y_grid)
        grid.add(Point{0, y}, Point{x_size, y});
    grid.set_color(Color::red);
    grid.set_style(Line_style(Line_style::dot, 3));
    win3.attach(grid);                      // Связываем линии с окном
    win3.wait_for_button();                 // Вывод


}

//-----------------------------------------------------------------------------

int main()
try {
    example13();
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

