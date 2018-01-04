//------------------------------------------------------------------------------

#include "Input_orders_window.hpp"

//------------------------------------------------------------------------------

using namespace Graph_lib;

//-----------------------------------------------------------------------------

Save_quit_window::Save_quit_window(Graph_lib::Point xy, int w, int h,
                                   const string& title)
    : Window{xy, w, h, title},
      save_button{Point{x_max()-150, 0}, 70, 20, "Save",
                  [] (Address, Address pw) {
                     reference_to<Save_quit_window>(pw).save_pressed();
                  }},
      quit_button{Point{x_max()-70, 0}, 70, 20, "Quit",
                  [] (Address, Address pw) {
                     reference_to<Save_quit_window>(pw).quit_pressed();
                  }}
{
    attach(save_button);
    attach(quit_button);
}

//------------------------------------------------------------------------------

Simple_orders_window::Simple_orders_window(Point xy, int w, int h,
                                           const string& title)
    : Save_quit_window{xy, w, h, title},
      fname_in{Point{x_max()-260, 0}, 100, 20, "File name"},
      order_nm_in{Point{140, 0}, 250, 20, "Name client"},
      order_addr_in{Point{140, 30}, 250, 20, "Address client"},
      order_dbirth_in{Point{140, 60}, 250, 20, "Date of birth client"},
      purchase_nm_in{Point{480, 0}, 125, 20, "Name unit"},
      purchase_price_in{Point{480, 30}, 125, 20, "Price unit"},
      purchase_count_in{Point{480, 60}, 125, 20, "Count unit"},
      add_order_button{Point{140, 90}, 110, 20, "Add order",
                       cb_add_order},
      add_purchase_button{Point{480, 90}, 110, 20, "Add purchase",
                          cb_add_purchase}
{
    attach(fname_in);
    attach(order_nm_in);
    attach(order_addr_in);
    attach(order_dbirth_in);
    attach(purchase_nm_in);
    attach(purchase_price_in);
    attach(purchase_count_in);

    attach(add_order_button);
    attach(add_purchase_button);

    orders.push_back(Order{});
}

//------------------------------------------------------------------------------

void Simple_orders_window::clear_all_in()
{
    order_nm_in.clear();
    order_addr_in.clear();
    order_dbirth_in.clear();

    purchase_nm_in.clear();
    purchase_price_in.clear();
    purchase_count_in.clear();
}

//------------------------------------------------------------------------------

void Simple_orders_window::save_pressed()
{

}

//------------------------------------------------------------------------------

void Simple_orders_window::add_order_pressed()
{
    orders.back().set_name(order_nm_in.get_string());
    orders.back().set_address(order_addr_in.get_string());
    orders.back().set_date_birth(order_dbirth_in.get_string());

    orders.push_back(Order{});

    order_nm_in.clear();
    order_addr_in.clear();
    order_dbirth_in.clear();
}

//------------------------------------------------------------------------------

void Simple_orders_window::add_purchase_pressed()
{
    Purchase p;
    p.name = purchase_nm_in.get_string();
    p.unit_price = purchase_price_in.get_double();
    p.count = purchase_count_in.get_int();
    orders.back().add(p);

    purchase_nm_in.clear();
    purchase_price_in.clear();
    purchase_count_in.clear();
}

//------------------------------------------------------------------------------

void Simple_orders_window::cb_add_order(Address, Address pw)
{
    reference_to<Simple_orders_window>(pw).add_order_pressed();
}

//------------------------------------------------------------------------------

void Simple_orders_window::cb_add_purchase(Address, Address pw)
{
    reference_to<Simple_orders_window>(pw).add_purchase_pressed();
}

//------------------------------------------------------------------------------

double Clear_in_box::get_double()
{
    Fl_Input& pi = reference_to<Fl_Input>(pw);
    const char* p = pi.value();
    if (!isdigit(p[0])) return -999999;
    return atof(p);
}

//------------------------------------------------------------------------------
