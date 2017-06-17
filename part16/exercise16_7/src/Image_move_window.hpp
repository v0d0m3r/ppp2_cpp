#ifndef IMAGE_MOVE_WINDOW_HPP
#define IMAGE_MOVE_WINDOW_HPP

//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/Common_window.hpp"

//-----------------------------------------------------------------------------

struct Image_move_window : public Action_window
{
    Image_move_window(Graph_lib::Point xy, int w, int h,
                      const string& title, const string& imgname)
        : Action_window(xy, w, h, title),
          img{xy, imgname}
    { attach(img); set_frequency(.2); }

protected:
    void do_action() override { img.move(10, 0); }

private:
    // Виджеты
    Graph_lib::Image img;    
};

//-----------------------------------------------------------------------------

#endif // IMAGE_MOVE_WINDOW_HPP
