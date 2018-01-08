//------------------------------------------------------------------------------

#include "Input_orders_window.hpp"

//------------------------------------------------------------------------------

using namespace Graph_lib;

//-----------------------------------------------------------------------------

Quit_window::Quit_window(Graph_lib::Point xy, int w, int h,
                         const string& title)
    : Window{xy, w, h, title},
      quit_button{Point{x_max()-70, 0}, 70, 20, "Quit",
                  [] (Address, Address pw) {
                     reference_to<Quit_window>(pw).quit_pressed();
                  }}
{
    attach(quit_button);
}

//-----------------------------------------------------------------------------

Save_quit_window::Save_quit_window(Graph_lib::Point xy, int w, int h,
                                   const string& title)
    : Quit_window{xy, w, h, title},
      save_button{Point{x_max()-150, 0}, 70, 20, "Save",
                  [] (Address, Address pw) {
                     reference_to<Save_quit_window>(pw).save_pressed();
                  }}

{
    attach(save_button);
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
      err_out{Point{50, y_max()-20}, 125, 20, "Error"},
      prepare_order_button{Point{140, 90}, 110, 20, "Next",
                           cb_prepare_order},
      add_order_button{Point{280, 90}, 110, 20, "Add order",
                       cb_add_order},
      set_order_button{Point{280, 90}, 110, 20, "Set order",
                       cb_set_order},
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
    attach(err_out);

    attach(prepare_order_button);
    attach(add_order_button);
    attach(set_order_button);
    attach(add_purchase_button);

    hide_purchase_feat();
    set_order_button.hide();
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

void Simple_orders_window::hide_purchase_feat()
{
    purchase_nm_in.hide();
    purchase_price_in.hide();
    purchase_count_in.hide();
    add_purchase_button.hide();
}

//------------------------------------------------------------------------------

void Simple_orders_window::show_purchase_feat()
{
    purchase_nm_in.show();
    purchase_price_in.show();
    purchase_count_in.show();
    add_purchase_button.show();
}

//------------------------------------------------------------------------------

void Simple_orders_window::save_pressed()
try
{
    err_out.put("");
    if (orders.empty()) error("Нет заказов!!");

    string fname{fname_in.get_string()};
    if (fname.empty()) error("file name is empty");

    ofstream ofs{"./" + fname, ios_base::app};
    if (!ofs)
        error("exercise_21_11: ", "Невозможно открыть выходной файл");

    std::copy(orders.begin(), orders.end(),
              ostream_iterator<Order>{ofs, "\n"});

    orders.clear();
    prepare_order_pressed();
    redraw();
}
catch (const exception& e) {
    err_out.put(e.what());
    redraw();
}

//------------------------------------------------------------------------------

void Simple_orders_window::prepare_order_pressed()
{
    clear_all_in();
    hide_purchase_feat();
    add_order_button.show();
}

//------------------------------------------------------------------------------

void Simple_orders_window::add_order_pressed()
try
{
    err_out.put("");
    Order ord {
        order_nm_in.get_string(),
        order_addr_in.get_string(),
        order_dbirth_in.get_string(),
        vector<Purchase>{}
    };
    orders.push_back(ord);

    show_purchase_feat();
    add_order_button.hide();
    set_order_button.show();

    redraw();
}
catch (const exception& e) {
    err_out.put(e.what());
    redraw();
}

//------------------------------------------------------------------------------

void Simple_orders_window::set_order_pressed()
try
{
    err_out.put("");
    orders.back().set_name(order_nm_in.get_string());
    orders.back().set_address(order_addr_in.get_string());
    orders.back().set_name(order_dbirth_in.get_string());

    redraw();
}
catch (const exception& e) {
    err_out.put(e.what());
    redraw();
}

//------------------------------------------------------------------------------

void Simple_orders_window::add_purchase_pressed()
try
{
    err_out.put("");
    Purchase p {
        purchase_nm_in.get_string(),
        purchase_price_in.get_double(),
        purchase_count_in.get_int()
    };
    orders.back().add(p);

    purchase_nm_in.clear();
    purchase_price_in.clear();
    purchase_count_in.clear();

    redraw();
}
catch (const exception& e) {
    err_out.put(e.what());
    redraw();
}

//------------------------------------------------------------------------------

void Simple_orders_window::cb_prepare_order(Address, Address pw)
{
    reference_to<Simple_orders_window>(pw).prepare_order_pressed();
}

//------------------------------------------------------------------------------

void Simple_orders_window::cb_add_order(Address, Address pw)
{
    reference_to<Simple_orders_window>(pw).add_order_pressed();
}

//------------------------------------------------------------------------------

void Simple_orders_window::cb_set_order(Address, Address pw)
{
    reference_to<Simple_orders_window>(pw).set_order_pressed();
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
