#include "my_window.h"

//-----------------------------------------------------------------------------

My_window::My_window(Point xy, int w, int h, const string &title)
    : Simple_window(xy, w,h,title),
      quit_button{Point{x_max()-70, 30}, 70, 20, "Quit",
                  [] (Address, Address pw)
                     {
                          reference_to<My_window>(pw).quit();
                     }
                  }
{    
    attach(quit_button);
}

//-----------------------------------------------------------------------------
