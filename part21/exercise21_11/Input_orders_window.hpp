//------------------------------------------------------------------------------

#ifndef INPUT_ORDERS_WINDOW_HPP
#define INPUT_ORDERS_WINDOW_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/GUI.h"
#include "../exercise21_9/Order.hpp"

//------------------------------------------------------------------------------

class Input_orders_window : public Graph_lib::Window
{
public:
    Input_orders_window(Graph_lib::Point xy, int w, int h,
                        const string& title);

private:
    // Виджеты
    Graph_lib::Button save_button;  // Сохраняет заказы
    Graph_lib::Button quit_button;  // Завершает работу программы

    Graph_lib::In_box orders_in;
    Graph_lib::In_box fname_in;

    // Действия
    void save_pressed();
    void quit_pressed() { hide(); }

    // Callback-функции
    static void cb_save(Graph_lib::Address, Graph_lib::Address);
    static void cb_quit(Graph_lib::Address, Graph_lib::Address);
};

//------------------------------------------------------------------------------

#endif // INPUT_ORDERS_WINDOW_HPP

//------------------------------------------------------------------------------
