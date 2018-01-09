//-----------------------------------------------------------------------------

#include "Query_orders_window.hpp"

//-----------------------------------------------------------------------------

using namespace Graph_lib;

//-----------------------------------------------------------------------------

Query_orders_window::Query_orders_window(Graph_lib::Point xy, int w, int h,
                                         const string& title)
    : Quit_window{xy, w, h, title},
      next_button{Point{x_max()-150, 0}, 70, 20, "Next", cb_next},
      fnd_by_nm_clnt_button{Point{210, 30}, 70, 20,
                            "Find", cb_fnd_by_nm_clnt},
      calc_total_sum_button{Point{210, 60}, 70, 20,
                            "Sum", cb_calc_total_sum},
      out_all_orders_button{Point{210, 90}, 70, 20,
                            "All orders", cb_out_all_orders},
      next_file_in{Point{x_max()-310, 0}, 100, 20, "next file:"},
      nm_clnt_in{Point{100, 30}, 100, 20, "name client:"},
      file_out{Point{100, 0}, 100, 20, "current file:"},
      queries_out{Point{100, 120}, x_max()-110, 20, "result:"}
{
    attach(next_button);
    attach(fnd_by_nm_clnt_button);
    attach(calc_total_sum_button);
    attach(out_all_orders_button);

    attach(next_file_in);
    attach(nm_clnt_in);
    attach(file_out);
    attach(queries_out);
}

//-----------------------------------------------------------------------------

void Query_orders_window::next()
try
{
    queries_out.put("");
    orders.clear();

    string fname{next_file_in.get_string()};
    if (fname.empty()) error("file name is empty");
    fill_from_file(orders, Cmp_by_name{}, "./" + fname);

    // Обновление текущей точки
    ostringstream ss;
    ss << fname;
    file_out.put(ss.str());

    redraw();
}
catch (const exception& e) {
    queries_out.put("error: " + to_string(e.what()));
    redraw();
}

//-----------------------------------------------------------------------------

void Query_orders_window::fnd_by_nm_clnt()
try
{
    queries_out.put("");

    string nm_clnt{nm_clnt_in.get_string()};
    if (nm_clnt.empty()) error("client name is empty");

    vector<Order> tmp(count_if(orders, Order_equal_name{nm_clnt}));
    copy_if(orders, tmp, Order_equal_name{nm_clnt});

    ostringstream ss;
    copy(tmp, ostream_iterator<Order>{ss, ";"});
    queries_out.put(ss.str());
    redraw();
}
catch (const exception& e) {
    queries_out.put("error: " + to_string(e.what()));
    redraw();
}

//-----------------------------------------------------------------------------

void Query_orders_window::calc_total_sum()
{
    ostringstream ss;
    ss << std::accumulate(orders.begin(), orders.end(),
                          0.0, sum_order_alternative);
    queries_out.put(ss.str());
    redraw();
}

//-----------------------------------------------------------------------------

void Query_orders_window::out_all_orders()
{
    ostringstream ss;
    copy(orders, ostream_iterator<Order>{ss, ";"});
    queries_out.put(ss.str());
    redraw();
}

//-----------------------------------------------------------------------------

void Query_orders_window::cb_next(Address, Address pw)
{
    reference_to<Query_orders_window>(pw).next();
}

//-----------------------------------------------------------------------------

void Query_orders_window::cb_fnd_by_nm_clnt(Address, Address pw)
{
    reference_to<Query_orders_window>(pw).fnd_by_nm_clnt();
}

//-----------------------------------------------------------------------------

void Query_orders_window::cb_calc_total_sum(Address, Address pw)
{
    reference_to<Query_orders_window>(pw).calc_total_sum();
}

//-----------------------------------------------------------------------------

void Query_orders_window::cb_out_all_orders(Address, Address pw)
{
    reference_to<Query_orders_window>(pw).out_all_orders();
}

//-----------------------------------------------------------------------------
