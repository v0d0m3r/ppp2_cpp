#ifndef FUNC_WINDOW_HPP
#define FUNC_WINDOW_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/GUI.h"

//------------------------------------------------------------------------------

class Func_window : public Graph_lib::Window
{
public:
    enum Input {
        r_min, r_max, count,
        xscale, yscale
    };

    Func_window(Graph_lib::Point xy, int w, int h,
                const string& title, Graph_lib::Funct& ff);

private:
    // Данные
    Graph_lib::Funct& f;

    // Виджеты
    Graph_lib::Vector_ref<Graph_lib::In_box> inboxs;
    Graph_lib::Button quit_button;
    Graph_lib::Menu func_menu;
    Graph_lib::Button menu_button;

    void recalculate(Graph_lib::Fct f);
    void load_func_inbox();

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

inline const string& get_name_in_box(Func_window::Input in)
{
    static const vector<string> names{
        "r_min", "r_min", "r_max", "orig_x",
        "orig_y", "count", "xscale", "yscale"
    };
    return names[in];
}

//------------------------------------------------------------------------------

#endif // FUNC_WINDOW_HPP
