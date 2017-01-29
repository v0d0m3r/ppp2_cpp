#ifndef FIGURES_WINDOW_H
#define FIGURES_WINDOW_H

//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/GUI.h"

//-----------------------------------------------------------------------------

using namespace Graph_lib;

//-----------------------------------------------------------------------------

class Figures_window : public Graph_lib::Window
{
public:
    Figures_window(Point xy, int w, int hh, const string& title);

protected:
    Shape& current_shape() { return *current; }

private:
    // Данные
    static constexpr double percent = 0.3;  // Процентный множитель
    int h;              // Высота окна
    Circle cir;
    Rectangle sq;
    Right_triangle rt;
    Regular_hexagon rh;
    Shape* current;     // Текущий объект связан с окном

    // Виджеты
    Button quit_button; // Завершает работу программы
    In_box next_x;
    In_box next_y;
    Menu figure_menu;

    void set_attached(Shape& s);

    // Действия
    void circle_pressed();
    void square_pressed();
    void triangle_pressed();
    void hexagon_pressed();
    void quit() { hide(); }

    // Callback-функции
    static void cb_circle  (Address, Address);
    static void cb_square  (Address, Address);
    static void cb_triangle(Address, Address);
    static void cb_hexagon (Address, Address);
    static void cb_quit    (Address, Address);
};

//-----------------------------------------------------------------------------

#endif // FIGURES_WINDOW_H
