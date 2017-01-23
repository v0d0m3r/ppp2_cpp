#ifndef CHESS_WINDOW_H
#define CHESS_WINDOW_H

//-----------------------------------------------------------------------------

#include "../../exercise16_1/exer16_1/my_window.h"

//-----------------------------------------------------------------------------

class Chess_window : public My_window
{
public:
    Chess_window(Point xy, int w, int h, const string& title);

private:
    Vector_ref<Rectangle> vr;
    Vector_ref<Button> vb;

    void change(int i)
    {

                vr[i].set_color(Color::red);
    }

};

//-----------------------------------------------------------------------------

#endif // CHESS_WINDOW_H
