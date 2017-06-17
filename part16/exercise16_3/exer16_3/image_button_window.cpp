#include "image_button_window.h"

//-----------------------------------------------------------------------------

Image_button_window::Image_button_window(Point xy, int w, int h,
                                         const string &title,
                                         const string &file_name,
                                         int r_min, int r_max)
    : My_window(xy, w, h, title),r1{r_min}, r2{r_max},
      ib{Point{w/2,h/2}, static_cast<int>(w*percent),
         static_cast<int>(h*percent), "",
         [] (Address, Address pw)
            {
                 reference_to<Image_button_window>(pw).rand_move();
            },
         file_name}
{
    attach(ib);
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
