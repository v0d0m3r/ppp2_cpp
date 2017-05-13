//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

/* Дано: точка О(x_max/2, y_max/2);
 * радиус окружности, которая описывает многоугольник
 * с максимальным количеством углов.
 * Алгоритм:
 * - делим окружность на n-кусков, и узнаем угол;
 * - находим координаты точек-вершин;
 * - соединяем вершины;
 * - "строим" трегольник между двумя соседними вершинами(кроме треугольника);
 * - находим высоту, которая будет считаться радиусом описаной окружности;
 * для следующего многоугольника;
*/

//-----------------------------------------------------------------------------

void find_dot(vector<Point>& dot_tb, int count_angle, double& radius)
{
    // Центр правильного многоугольника
    static const Point circle_mid{Graph_lib::x_max()/2, Graph_lib::y_max()/2};
    const double delta_angle = 360 / count_angle;;
    double angle = 0.00; // Угол наклона правильного многоугольника
    Point current{0, 0};
    for (int i=0; i < count_angle; ++i) {
        current.x = circle_mid.x + radius * cos(angle * M_PI/180.0);
        current.y = circle_mid.y + radius * sin(angle * M_PI/180.0);
        dot_tb.push_back(current);
        angle += delta_angle; // Увеличиваем угол на величину
                              // угла правильного многоугольника
    }
    // Поиск n-1 радиуса
    double end_new_radius_x = (dot_tb[0].x + dot_tb[1].x) / 2.0;
    double end_new_radius_y = (dot_tb[0].y + dot_tb[1].y) / 2.0;
    double vect_new_radius_x = end_new_radius_x - circle_mid.x;
    double vect_new_radius_y = end_new_radius_y - circle_mid.y;
    radius = sqrt(pow(vect_new_radius_x, 2) + pow(vect_new_radius_y, 2));
}

//-----------------------------------------------------------------------------

void paint_polygon(const vector<Point>& dot_tb,
                   Graph_lib::Open_polyline& regular_polygon)
{
    for (const Point& p : dot_tb)
        regular_polygon.add(p);

    regular_polygon.add(dot_tb[0]);
}

//-----------------------------------------------------------------------------

void regular_polygon()
{
    using namespace Graph_lib;
    cout << "Введите через пробел максимальное "
         << "количество углов и радиус максимальной окружности :\n";
    int count_angle;
    double radius;
    cin >> count_angle >> radius;
    if (!cin) error("Ошибка ввода количества углов");
    vector<Point> dot_tb;
    Point t1{0, 0};
    Simple_window win{t1, x_max(), y_max(), "Canvas #12_11"};

    Open_polyline regular_polygon;
    Open_polyline regular_polygon2;
    Open_polyline regular_polygon3;
    Vector_ref<Shape> t;
    t.push_back(regular_polygon);

    Line line{Point{0,0},Point{x_max()/2, y_max()/2}};

    win.attach(line);

    find_dot(dot_tb, count_angle, radius);
    paint_polygon(dot_tb, regular_polygon);
    dot_tb.clear();
    --count_angle;

    Point circle_mid{Graph_lib::x_max()/2, Graph_lib::y_max()/2};
    Circle circ{circle_mid, radius};

    find_dot(dot_tb, count_angle, radius);
    paint_polygon(dot_tb, regular_polygon2);
    dot_tb.clear();
    --count_angle;
    Circle circ1{circle_mid, radius};
    find_dot(dot_tb, count_angle, radius);
    paint_polygon(dot_tb, regular_polygon3);

    win.attach(regular_polygon);
    win.attach(regular_polygon2);
    win.attach(regular_polygon3);
    win.attach(circ);
    win.attach(circ1);



    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    regular_polygon();
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
    return -2;
}

//-----------------------------------------------------------------------------
