//-----------------------------------------------------------------------------

#include "Analog_clock_window.hpp"

using namespace Graph_lib;

//-----------------------------------------------------------------------------

Analog_clock_window::Analog_clock_window(Point xy, int w, int h,
                                         const string& title)
    : Action_window(xy, w, h, title),
      aclock{Point{x_max()/2, y_max()/2}, 100}

{
    attach(aclock);   
}

//-----------------------------------------------------------------------------
