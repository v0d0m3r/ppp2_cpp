// Exercise 13_6
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

void exercise()
{
    const Point x{0, 0};
    Simple_window win{x, 1200, 800, "exercise 13_6"};

    constexpr int height = 30;

    Texted_box wind{Point{140, 100}, 80, height, "Window"};
    win.attach(wind);
    Texted_box line_style{Point{240, 100}, 90, height, "Line_style"};
    win.attach(line_style);
    Texted_box color{Point{390, 100}, 65, height, "Color"};
    win.attach(color);
    Texted_box swind{Point{130, 200}, 100, height, "Simple_text"};
    win.attach(swind);
    Texted_box shape{Point{280, 180}, 70, height, "Shape"};
    win.attach(shape);
    Texted_box point{Point{410, 200}, 70, height, "Point"};
    win.attach(point);
    Texted_box line{Point{80, 340}, 50, height, "Line"};
    win.attach(line);
    Texted_box lines{Point{140, 340}, 55, height, "Lines"};
    win.attach(lines);
    Texted_box polygon{Point{205, 340}, 75, height, "Polygon"};
    win.attach(polygon);
    Texted_box axis{Point{290, 340}, 50, height, "Axis"};
    win.attach(axis);
    Texted_box rect{Point{350, 340}, 90, height, "Rectangle"};
    win.attach(rect);
    Texted_box text{Point{450, 340}, 50, height, "Text"};
    win.attach(text);
    Texted_box image{Point{510, 340}, 60, height, "Image"};
    win.attach(image);

    Arrow wind_to_swind{w(swind), e(wind)};
    win.attach(wind_to_swind);
    Arrow line_to_shape{w(line), Point{e(shape).x-28,
                        e(shape).y-3}};
    win.attach(line_to_shape);
    Arrow lines_to_shape{w(lines), Point{e(shape).x-17,
                         e(shape).y}};
    win.attach(lines_to_shape);
    Arrow polygon_to_shape{w(polygon), Point{e(shape).x-7,
                           e(shape).y}};
    win.attach(polygon_to_shape);
    Arrow axis_to_shape{w(axis), e(shape)};
    win.attach(axis_to_shape);
    Arrow rect_to_shape{w(rect), Point{e(shape).x+7,
                        e(shape).y}};
    win.attach(rect_to_shape);
    Arrow text_to_shape{w(text), Point{e(shape).x+17,
                        e(shape).y}};
    win.attach(text_to_shape);
    Arrow image_to_shape{w(image), Point{e(shape).x+28,
                        e(shape).y-3}};
    win.attach(image_to_shape);


    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    exercise();
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
