#ifndef FUNC_WINDOW_HPP
#define FUNC_WINDOW_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/GUI.h"

//------------------------------------------------------------------------------

class Func_window : public Graph_lib::Window
{
public:
    Func_window(Graph_lib::Point xy, int w, int h,
                const string& title, Graph_lib::Funct& ff);

private:
    // Данные
    Graph_lib::Funct& f;

    // Виджеты
    Graph_lib::Button quit_button;

    Graph_lib::In_box r_min_in_box;
    Graph_lib::In_box r_max_in_box;
    Graph_lib::In_box count_in_box;
    Graph_lib::In_box xscale_in_box;
    Graph_lib::In_box yscale_in_box;

    Graph_lib::Menu func_menu;
    Graph_lib::Button menu_button;

    void recalculate(Graph_lib::Fct ff);
    void load_func_menu();

    void hide_menu() { func_menu.hide(); menu_button.show(); }

    // Действия инициируемые обратными вызовами
    void sin_pressed()  { recalculate(sin); hide_menu();}
    void cos_pressed()  { recalculate(cos); hide_menu();}
    void exp_pressed()  { recalculate(exp); hide_menu();}
    void menu_pressed() { menu_button.hide();func_menu.show(); }
    void quit() { hide(); }

    // Callback-функции
    static void cb_sin(Graph_lib::Address, Graph_lib::Address);
    static void cb_cos(Graph_lib::Address, Graph_lib::Address);
    static void cb_exp(Graph_lib::Address, Graph_lib::Address);
    static void cb_menu(Graph_lib::Address, Graph_lib::Address);
    static void cb_quit(Graph_lib::Address, Graph_lib::Address);

};

//------------------------------------------------------------------------------

#endif // FUNC_WINDOW_HPP
