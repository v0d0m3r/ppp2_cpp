#include "image_button_window.h"

//-----------------------------------------------------------------------------

Image_button_window::Image_button_window(Point xy, int w, int h,
                                         const string &title,
                                         const string &file_name,
                                         int r_min, int r_max)
    : My_window(xy, w, h, title),r1{r_min}, r2{r_max},
      ib{Point{w/2,h/2}, w*percent, h*percent, "",
         [] (Address, Address pw)
            {
                 reference_to<Image_button_window>(pw).rand_move();
            },
         file_name}
{
    attach(ib);
}

//-----------------------------------------------------------------------------

void Image_button_window::attach(Image_button &ib)
{
    My_window::attach(ib);
    My_window::attach(ib.image());
}

//-----------------------------------------------------------------------------

void Image_button_window::detach(Image_button &ib)
{
    My_window::detach(ib);
    My_window::detach(ib.image());
}

//-----------------------------------------------------------------------------

inline int rand_int(int min, int max)
{
    static default_random_engine ran;
    return uniform_int_distribution<>{min, max}(ran);
}

//-----------------------------------------------------------------------------

void Image_button_window::rand_move()
{
    ib.move(rand_int(r1, r2), rand_int(r1, r2));
}

//-----------------------------------------------------------------------------
