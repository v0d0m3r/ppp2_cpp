//-----------------------------------------------------------------------------

#ifndef QUERY_ORDERS_WINDOW_HPP
#define QUERY_ORDERS_WINDOW_HPP

//-----------------------------------------------------------------------------

#include "../exercise21_11/Input_orders_window.hpp"

//-----------------------------------------------------------------------------

class Query_orders_window : public Quit_window
{
public:
    Query_orders_window(Graph_lib::Point xy, int w, int h,
                        const string& title);

private:
    // Данные
    vector<Order> orders;

    // Виджеты
    Graph_lib::Button next_button;  // Считывает данные
                                    // из файла
    Graph_lib::Button fnd_by_nm_clnt_button; // Поиск заказов
                                             // по имени клиента
    Graph_lib::Button calc_total_sum_button; // Вычислить общую сумму
    Graph_lib::Button out_all_orders_button; // Вывести все заказы

    Graph_lib::In_box next_file_in; // Имя следующего файла
    Graph_lib::In_box nm_clnt_in;   // Имя клиента

    Graph_lib::Out_box file_out;    // Имя текущего файла
    Graph_lib::Out_box queries_out; // Вывод результатов запросов

    // Действия
    void next();
    void fnd_by_nm_clnt();
    void calc_total_sum();
    void out_all_orders();

    // Callback-функции
    static void cb_next          (Graph_lib::Address, Graph_lib::Address);
    static void cb_fnd_by_nm_clnt(Graph_lib::Address, Graph_lib::Address);
    static void cb_calc_total_sum(Graph_lib::Address, Graph_lib::Address);
    static void cb_out_all_orders(Graph_lib::Address, Graph_lib::Address);
};

//-----------------------------------------------------------------------------

#endif // QUERY_ORDERS_WINDOW_HPP

//-----------------------------------------------------------------------------
