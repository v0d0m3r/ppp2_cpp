// Задания к главе 13
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void task()
{
    using namespace Graph_lib;
    const Graph_lib::Point x{0, 0};
    Simple_window win{x, 800, 1000, "rects"};

    Vector_ref<Rectangle> vr;
    constexpr int rows = 8;
    constexpr int columns = 8;
    constexpr int rect_width = 100;
    constexpr int rect_height = 100;
    // Сетка 8Х8 из прямоугольников
    for (int i=0; i < columns; ++i)
        for (int j=0; j < rows; ++j) {
            vr.push_back(new Rectangle{Point{i*rect_width, j*rect_height},
                                       rect_width, rect_height});
            if (i == j) // Закрашиваем по диагонали
                vr[vr.size()-1].set_fill_color(Color::red);
            win.attach(vr[vr.size()-1]);
        }
    Vector_ref<Image> ivr;
    constexpr int img_height = 200;
    constexpr int img_width = 200;
    // 2 объекта изображения поверх сетки
    for (int i=1; i < 3; ++i) {
        ivr.push_back(new Image{Point{i*img_width, 0}, "1.jpg"});
        ivr[ivr.size()-1].set_mask(Point{200,200},
                                   img_width, img_height);
        win.attach(ivr[ivr.size()-1]);
    }
    win.wait_for_button();
    Image img{Point{0, 0}, "1.jpg"};
    img.set_mask(Point{200,200}, rect_width, rect_height);
    win.attach(img);
    // Перемещаем изображение по сетке
    for (int i=0; i < columns; ++i) {
        for (int j=0; j < rows; ++j) {
            if (j != 0) img.move(0, rect_height);
            win.wait_for_button();
        }
        // Перемещаем на новый столцец в верх
        img.move(rect_width, -(rows-1)*rect_height);
    }
}

//-----------------------------------------------------------------------------

int main()
try {
    task();
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
