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
    int item_on_line = 4;       // Количество кнопок в строке
    Vector_ref<Rectangle> vr;   // Каждой кнопки соответсвует
                                // свой прямоугольник
    Vector_ref<Button> vb;
    void clear();
    void change(int i);         // Изменение цвета прямоугольника
    // Вектор функций обратного вызова
    vector<Callback> vc {
        [] (Address, Address pw) { reference_to<Chess_window>(pw).change(0);},
        [] (Address, Address pw) { reference_to<Chess_window>(pw).change(1);},
        [] (Address, Address pw) { reference_to<Chess_window>(pw).change(2);},
        [] (Address, Address pw) { reference_to<Chess_window>(pw).change(3);},
        [] (Address, Address pw) { reference_to<Chess_window>(pw).change(4);},
        [] (Address, Address pw) { reference_to<Chess_window>(pw).change(5);},
        [] (Address, Address pw) { reference_to<Chess_window>(pw).change(6);},
        [] (Address, Address pw) { reference_to<Chess_window>(pw).change(7);},
        [] (Address, Address pw) { reference_to<Chess_window>(pw).change(8);},
        [] (Address, Address pw) { reference_to<Chess_window>(pw).change(9);},
        [] (Address, Address pw) { reference_to<Chess_window>(pw).change(10);},
        [] (Address, Address pw) { reference_to<Chess_window>(pw).change(11);},
        [] (Address, Address pw) { reference_to<Chess_window>(pw).change(12);},
        [] (Address, Address pw) { reference_to<Chess_window>(pw).change(13);},
        [] (Address, Address pw) { reference_to<Chess_window>(pw).change(14);},
        [] (Address, Address pw) { reference_to<Chess_window>(pw).change(15);}
    };
};

//-----------------------------------------------------------------------------

#endif // CHESS_WINDOW_H
