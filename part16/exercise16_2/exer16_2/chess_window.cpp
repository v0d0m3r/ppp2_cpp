#include "chess_window.h"

//-----------------------------------------------------------------------------

Chess_window::Chess_window(Point xy, int w, int h, const string &title)
    : My_window(xy, w, h, title)
{
    const int item_size = h / item_on_line;            // Ширина ячейки
    const int item_line_size = item_on_line*item_size; // Ширина строки ячеек
    const int delta = (h - item_line_size) / 2;        // Погрешность
    Point p{0, 0};
    int counter = 0;
    for (int y=0; y < item_line_size; y += item_size) {
        for (int x=0; x < item_line_size; x += item_size) {
            if (counter < vc.size()) {
                vb.push_back(new Button{Point{p.x + x + delta,
                                              p.y + y + delta},
                                        item_size, item_size,
                                        "",vc[counter]
                                        });
                attach(vb[vb.size() -1]);
                // Добавляем заполнение кнопок
                vr.push_back(new Rectangle{Point{p.x + x + delta,
                                                 p.y + y + delta},
                                           item_size, item_size});
                attach(vr[vr.size() -1]);
            }
            ++counter;
        }
    }
    init();
}

//-----------------------------------------------------------------------------

void Chess_window::change(int i)
{
    // Возвращаем цвет по умолчанию
    if (cur_rect) cur_rect->set_fill_color(prev_col);

    // Запоминаем объект и его предыдущий цвет
    cur_rect = &vr[i];
    prev_col = vr[i].fill_color();

    cur_rect->set_fill_color(Color::red);    // Делаем объект "активным"

    redraw();
}

//-----------------------------------------------------------------------------
// init() заполняет доску
void Chess_window::init()
{
    int parity = 0;
    int counter = 0;
    for (int i=0; i < vr.size(); ++i) {
        if (item_on_line%2==0 && counter%item_on_line==0)
            ++parity;

        (parity%2 != 0) ? vr[i].set_fill_color(Color::black)
                        : vr[i].set_fill_color(Color::white);
        ++parity;
        ++counter;
    }
}

//-----------------------------------------------------------------------------
