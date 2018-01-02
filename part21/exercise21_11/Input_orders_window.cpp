//------------------------------------------------------------------------------

#include "Input_orders_window.hpp"

//------------------------------------------------------------------------------

using namespace Graph_lib;

//-----------------------------------------------------------------------------

Input_orders_window::Input_orders_window(Graph_lib::Point xy, int w, int h,
                                         const string& title)
    : Window(xy, w, h, title),
      save_button{Point{x_max()-150, 0}, 70, 20, "Save", cb_save},
      quit_button{Point{x_max()-70, 0}, 70, 20, "Quit", cb_quit},
      orders_in{Point{x_max()-450, 0}, 50, 20, "Orders"},
      fname_in {Point{x_max()-330, 0}, 50, 20, "File name"}
{
    attach(save_button);
    attach(quit_button);

    attach(orders_in);
    attach(fname_in);
}

//------------------------------------------------------------------------------

// Сохраняем заказ в файл
void Input_orders_window::save_pressed()
{
    ofstream ofs{"./" + fname_in.get_string()};
    if (!ofs)
        error("exercise_21_11: ", "Невозможно открыть выходной файл");

    istringstream is{orders_in.get_string()};
    std::copy(istream_iterator<Order>{is}, istream_iterator<Order>{},
              ostream_iterator<Order>{ofs, "\n"});
    redraw();
}

//------------------------------------------------------------------------------

void Input_orders_window::cb_save(Address, Address pw)
{
    reference_to<Input_orders_window>(pw).save_pressed();
}

//------------------------------------------------------------------------------

void Input_orders_window::cb_quit(Address, Address pw)
{
    reference_to<Input_orders_window>(pw).quit_pressed();
}

//------------------------------------------------------------------------------
