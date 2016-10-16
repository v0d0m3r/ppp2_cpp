// exercise13_12_13
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------
// Получаем точку на окружности,
// по заданным точке центра, радиусу и углу
Point get_point_oncircle(const Circle& cir, int angle)
{
    return Point{
        cir.center().x + cir.radius() * cos(angle * M_PI/180.0),
        cir.center().y + cir.radius() * sin(angle * M_PI/180.0)
    };
}

//-----------------------------------------------------------------------------

void exercise13_12()
{
    constexpr int delta_angle = 15;

    Simple_window win{Point {0, 0}, 1200, 800, "exercise 13_12"};

    Circle cir{Point{400, 400}, 200};
    Mark m{Point{0, 0}, 'M'};

    win.attach(cir);
    win.attach(m);

    for (int i = 0; i <= 360; i += delta_angle) {
        m.move(get_point_oncircle(cir, i).x - m.point(0).x,  // Сдвиг по ОХ
               get_point_oncircle(cir, i).y - m.point(0).y); // Сдвиг по ОУ
        win.wait_for_button();
    }

    win.wait_for_button();
}

//-----------------------------------------------------------------------------

void exercise13_13()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 13_13"};

    Vector_ref<Rectangle> vr;
    for (int i=0; i < 16; ++i)
        for (int j=0; j < 16; ++j) {
            vr.push_back(new Rectangle{Point{i*20, j*20}, 20, 20});
            vr[vr.size()-1].set_fill_color(Color{i*16+j});
            vr[vr.size()-1].set_color(Color::invisible);
            win.attach(vr[vr.size()-1]);
        }

    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    //exercise13_12();
    exercise13_13();
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
