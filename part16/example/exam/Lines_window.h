#ifndef LINES_WINDOW_H
#define LINES_WINDOW_H

#include "../../../bstroustrup_code/GUI.h"

//-----------------------------------------------------------------------------

using namespace Graph_lib;

//-----------------------------------------------------------------------------

class Lines_window : Graph_lib::Window
{
public:
    Lines_window(Point xy, int w, int h,
                 const string& title);
private:
    // Данные
    Open_polyline lines;

    // Виджеты
    Button next_button; // Добавляет пару (next_x, next_y)
                        // в объект lines
    Button quit_button; // Завершает работу программы
    In_box next_x;
    In_box next_y;
    Out_box xy_out;
    Menu color_menu;
    Button c_menu_button;
    Menu line_style_menu;
    Button ls_menu_button;

    void change(Color c) { lines.set_color(c);}
    void change_ls(Line_style ls) { lines.set_style(ls); }

    void hide_c_menu()  { color_menu.hide(); c_menu_button.show();}
    void hide_ls_menu() { line_style_menu.hide(); ls_menu_button.show();}

    // Действия
    void red_pressed()    { change(Color::red);   hide_c_menu(); redraw();}
    void blue_pressed()   { change(Color::blue);  hide_c_menu(); redraw();}
    void black_pressed()  { change(Color::black); hide_c_menu(); redraw();}
    void c_menu_pressed() { c_menu_button.hide(); color_menu.show(); redraw();}
    void solid_pressed();
    void dot_pressed();
    void dash_pressed();
    void ls_menu_pressed()
    { ls_menu_button.hide(); line_style_menu.show(); redraw();}
    void next();
    void quit() { hide(); }

    // Callback-функции
    static void cb_red    (Address, Address);
    static void cb_blue   (Address, Address);
    static void cb_black  (Address, Address);
    static void cb_c_menu (Address, Address);
    static void cb_solid  (Address, Address);
    static void cb_dot    (Address, Address);
    static void cb_dash   (Address, Address);
    static void cb_ls_menu(Address, Address);
    static void cb_next   (Address, Address);
    static void cb_quit   (Address, Address);
};

//-----------------------------------------------------------------------------

#endif // LINES_WINDOW_H
