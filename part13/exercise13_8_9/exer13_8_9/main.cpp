/*
Exercise 13_8_9
Задача: покрыть часть экрана мозаикой(не менее 8 Regular_hexagon).
Построим Regular_hexagon в середине, и относительно
его будем строить остальные.
Алгоритм:
1. Строим "главный" Regular_hexagon
2. Находим координаты центров первой линии
(первая линия - первые шесть Regular_hexagon
вокруг "главного"), координаты центров лежат
на вершинах Regular_hexagon, повернутый на 30 градусов, и большим радиусом.
3. Находим координаты центров остальных линий
4. Выводим на экран
*/
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void paint_hexagon()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 13_8_9"};
    const Point center{400, 400};
    constexpr int radius = 60;

    Vector_ref<Regular_hexagon> vr;
    vr.push_back(new Regular_hexagon{center, radius});  // Создаем "главный"
    vr[vr.size()-1].set_fill_color(Color::blue);
    vr[vr.size()-1].set_style(Line_style{Line_style::solid, 3});
    win.attach(vr[vr.size()-1]);

    vector<Point> points;
    int count_angle = 6;
    double rotation = 30.00;
    // Находим вершины большого regular_hexagon
    find_dot_reg_poly(points,center, count_angle,
                      2*radius,rotation);
    for (int i=0; i < points.size(); ++i) { // Создаем хексагоны первой линии
        vr.push_back(new Regular_hexagon{points[i], radius});
        vr[vr.size()-1].set_fill_color(i*20);
        vr[vr.size()-1].set_style(Line_style{Line_style::solid, 3});
        win.attach(vr[vr.size()-1]);
    }

    points.clear(); // Очищаем координаты
    find_dot_reg_poly(points, center, count_angle,
                      4*radius,rotation);

    vr.push_back(new Regular_hexagon{points[0], radius});
    vr[vr.size()-1].set_fill_color(vr.size()*20);
    vr[vr.size()-1].set_style(Line_style{Line_style::solid, 3});
    win.attach(vr[vr.size()-1]);
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    paint_hexagon();
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
