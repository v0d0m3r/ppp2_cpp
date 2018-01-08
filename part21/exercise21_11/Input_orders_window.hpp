//------------------------------------------------------------------------------

#ifndef INPUT_ORDERS_WINDOW_HPP
#define INPUT_ORDERS_WINDOW_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/GUI.h"
#include "../exercise21_9/Order.hpp"

//------------------------------------------------------------------------------

struct Clear_in_box : public Graph_lib::In_box {
    using Graph_lib::In_box::In_box;

    void clear()
        { Graph_lib::reference_to<Fl_Input>(pw).value(""); }

    double get_double();
};

//------------------------------------------------------------------------------

class Quit_window : public Graph_lib::Window
{
public:
    Quit_window(Graph_lib::Point xy, int w, int h,
                const string& title);

private:
    Graph_lib::Button quit_button;  // Завершает работу программы

    void quit_pressed() { hide(); }
};

//------------------------------------------------------------------------------

class Save_quit_window : public Quit_window
{
public:
    Save_quit_window(Graph_lib::Point xy, int w, int h,
                     const string& title);
protected:
    virtual void save_pressed() = 0;

private:
    // Виджеты
    Graph_lib::Button save_button;  // Сохраняет  
};

//------------------------------------------------------------------------------

class Simple_orders_window : public Save_quit_window
{
public:
    Simple_orders_window(Graph_lib::Point xy, int w, int h,
                         const string& title);
protected:
    virtual void save_pressed() override;

private:
    // Данные
    vector<Order> orders;

    // Виджеты
    Graph_lib::In_box fname_in;

    Clear_in_box order_nm_in;
    Clear_in_box order_addr_in;
    Clear_in_box order_dbirth_in;

    Clear_in_box purchase_nm_in;
    Clear_in_box purchase_price_in;
    Clear_in_box purchase_count_in;
    Graph_lib::Out_box err_out;

    Graph_lib::Button prepare_order_button;
    Graph_lib::Button add_order_button;
    Graph_lib::Button set_order_button;
    Graph_lib::Button add_purchase_button;

    void clear_all_in();
    void clear_purchase_feat();
    void hide_purchase_feat();
    void show_purchase_feat();

    // Действия
    void prepare_order_pressed();
    void add_order_pressed();
    void set_order_pressed();
    void add_purchase_pressed();

    // Callback-функции
    static void cb_prepare_order(Graph_lib::Address, Graph_lib::Address);
    static void cb_add_order(Graph_lib::Address, Graph_lib::Address);
    static void cb_set_order(Graph_lib::Address, Graph_lib::Address);
    static void cb_add_purchase(Graph_lib::Address, Graph_lib::Address);
};

//------------------------------------------------------------------------------

#endif // INPUT_ORDERS_WINDOW_HPP

//------------------------------------------------------------------------------
