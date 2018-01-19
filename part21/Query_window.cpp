//------------------------------------------------------------------------------

#include "Query_window.hpp"

//------------------------------------------------------------------------------

namespace Graph_lib {

//------------------------------------------------------------------------------

Quit_window::Quit_window(Graph_lib::Point xy, int w, int h,
                         const string& title)
    : Window{xy, w, h, title},
      qb{Point{x_max()-70, 0}, 70, 20, "Quit",
         [] (Address, Address pw) {
            reference_to<Quit_window>(pw).quit_pressed();
         }}
{
    attach(qb);
}

//------------------------------------------------------------------------------

Plain_window::Plain_window(Point xy, int w, int h, const string& title)
    : Quit_window{xy, w, h, title},
      plain_in{Point{x_max()-260, 0}, 100, 20, ""},
      plain_out{Point{100, 120}, x_max()-110, 20, ""},
      plain_button{Point{x_max()-150, 0}, 70, 20, "",
                   [] (Address, Address pw) {
                      reference_to<Plain_window>(pw).plain_pressed();
                   }}

{
    // attach()
    // attach(plain_button);
}

//------------------------------------------------------------------------------

Simple_order_window::Simple_order_window(Point xy, int w, int h,
                                         const string& title)
    : Plain_window{xy, w, h, title},
      order_nm_in{Point{140, 0}, 250, 20, "Name client"}
{
}

//------------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
