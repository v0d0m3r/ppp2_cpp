//------------------------------------------------------------------------------

#ifndef QUERY_WINDOW_HPP
#define QUERY_WINDOW_HPP

//------------------------------------------------------------------------------

#include "../bstroustrup_code/std_lib_facilities.h"
#include "../../bstroustrup_code/GUI.h"
#include "../exercise21_9/Order.hpp"

//------------------------------------------------------------------------------

namespace Graph_lib {

//------------------------------------------------------------------------------

struct Clear_in_box : public In_box {
    using In_box::In_box;

    void clear() { reference_to<Fl_Input>(pw).value(""); }
    double get_double();
};

//------------------------------------------------------------------------------

class Quit_window : public Window {
public:
    Quit_window(Point xy, int w, int h, const string& title);

protected:
    const Button& quit_button() const { return qb; }

private:
    Button qb;  // Завершает работу программы
    void quit_pressed() { hide(); }
};

//------------------------------------------------------------------------------

class Plain_window : public Quit_window {
public:
    Plain_window(Point xy, int w, int h, const string& title);

protected:
    In_box plain_in;
    Out_box plain_out;

    Button plain_button;
    virtual void plain_pressed() = 0;
};

//------------------------------------------------------------------------------

class Plain_order_window : public Plain_window {
public:
    Plain_order_window(Point xy, int w, int h, const string& title);

protected:
    virtual void plain_pressed() override {}

    vector<Order> orders;       // Информация о заказах
    Clear_in_box order_nm_in;
};

//------------------------------------------------------------------------------

class Input_order_window : public Plain_order_window {
public:
    Input_order_window(Point xy, int w, int h, const string& title);

protected:
    virtual void plain_pressed() override;

private:
    Clear_in_box order_addr_in;
    Clear_in_box order_dbirth_in;

    Clear_in_box purchase_nm_in;
    Clear_in_box purchase_price_in;
    Clear_in_box purchase_count_in;

    Button prepare_order_button;
    Button add_order_button;
    Button set_order_button;
    Button add_purchase_button;

    void init();
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

class Query_order_window : public Plain_order_window {
public:
    Query_order_window(Point xy, int w, int h, const string& title);

protected:
    virtual void plain_pressed() override;

private:
    Button fnd_by_nm_clnt_button; // Поиск заказов
                                  // по имени клиента
    Button calc_total_sum_button; // Вычислить общую сумму
    Button out_all_orders_button; // Вывести все заказы

    Out_box file_out;    // Имя текущего файла

    void init();

    // Действия
    void fnd_by_nm_clnt();
    void calc_total_sum();
    void out_all_orders();

    // Callback-функции
    static void cb_fnd_by_nm_clnt(Graph_lib::Address, Graph_lib::Address);
    static void cb_calc_total_sum(Graph_lib::Address, Graph_lib::Address);
    static void cb_out_all_orders(Graph_lib::Address, Graph_lib::Address);

};

//------------------------------------------------------------------------------

class Finder_window : public Plain_window {
public:
    Finder_window(Point xy, int w, int h, const string& title);
protected:
    virtual void plain_pressed() override;
};

//------------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif // QUERY_WINDOW_HPP

//------------------------------------------------------------------------------
