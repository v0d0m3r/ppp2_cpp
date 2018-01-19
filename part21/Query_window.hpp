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

class Simple_order_window : public Plain_window {
public:
    Simple_order_window(Point xy, int w, int h, const string& title);

protected:
    vector<Order> orders;       // Информация о заказах
    Clear_in_box order_nm_in;
};

//------------------------------------------------------------------------------

class Input_order_window : public Simple_order_window {
public:
    Input_order_window(Point xy, int w, int h, const string& title);

protected:
};

//------------------------------------------------------------------------------

class Query_order_window : public Simple_order_window {
public:
    Query_order_window(Point xy, int w, int h, const string& title);

protected:
};

//------------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif // QUERY_WINDOW_HPP

//------------------------------------------------------------------------------
