//------------------------------------------------------------------------------

#include "Query_orders_window.hpp"

//------------------------------------------------------------------------------

using namespace Graph_lib;

//-----------------------------------------------------------------------------

void find_orders(const vector<Order>& vo)
{
    string name_client;
    cin >> name_client;

    vector<Order> tmp(count_if(vo, Order_equal_name{name_client}));
    copy_if(vo, tmp, Order_equal_name{name_client});
    copy(tmp, ostream_iterator<Order>{cout, "\n"});
}

//-----------------------------------------------------------------------------

void print_total_sum(const vector<Order>& vo)
{
    cout << std::accumulate(vo.begin(), vo.end(),
                            0.0, sum_order_alternative);
}

//-----------------------------------------------------------------------------

void print_all_orders(const vector<Order>& vo)
{
    copy(vo, ostream_iterator<Order>{cout, "\n"});
}

//-----------------------------------------------------------------------------

void exercise21_12()
{
    vector<Order> orders;
    const string fname{"./data1.txt"};
    fill_from_file(orders, Cmp_by_name{}, fname);
    find_orders(orders);
    print_total_sum(orders);
    print_all_orders(orders);
}

//-----------------------------------------------------------------------------

int main()
try
{
    Query_orders_window qow{Point{100, 100}, 1024, 800, "Order"};
    return gui_main();
    return 0;
}
catch (const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "oops!";
    return -2;
}

//------------------------------------------------------------------------------
