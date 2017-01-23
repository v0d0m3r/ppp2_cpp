#include "chess_window.h"

//-----------------------------------------------------------------------------

Chess_window::Chess_window(Point xy, int w, int h, const string &title)
    : My_window(xy, w, h, title)
{
    constexpr int height = 200;
    constexpr int item_on_line = 4;
    const int item_size = height / item_on_line;       // Ширина ячейки
    const int item_line_size = item_on_line*item_size; // Ширина строки ячеек
    const int delta = (height - item_line_size) / 2;   // Погрешность
    Point p{100, 100};
    for (int y=0; y < item_line_size; y += item_size) {
        for (int x=0; x < item_line_size; x += item_size) {
            vb.push_back(new Button{Point{p.x + x + delta,
                                          p.y + y + delta},
                                    item_size, item_size,
                                    "",
                                    Callback_capture([x] (Address, Address pw)
                                    {

                                        reference_to<Chess_window>(pw).change(x);
                                        ;
                                    })});
            attach(vb[vb.size() -1]);
            // Добавляем ячейки
            vr.push_back(new Rectangle{Point{p.x + x + delta,
                                             p.y + y + delta},
                                       item_size, item_size});
            attach(vr[vr.size() -1]);


        }
    }

}

//-----------------------------------------------------------------------------
