#ifndef IMAGE_BUTTON_WINDOW_H
#define IMAGE_BUTTON_WINDOW_H

//-----------------------------------------------------------------------------

#include "../../exercise16_1/exer16_1/my_window.h"
#include <random>

//-----------------------------------------------------------------------------
// Image_button представляет понятие "кнопка с картинкой"
class Image_button : public Button
{
public:
    Image_button(Point xy, int w, int h, const string& label,
                 Callback cb, const string& file_name)
        : Button(xy, w, h, label, cb), img{xy, file_name}
    {
        img.set_mask(Point{0, 0}, w, h);
    }

    void attach(Graph_lib::Window& w) override
    { Button::attach(w); w.attach(img); }

    void move(int dx,int dy) override
    { Button::move(dx, dy); img.move(dx, dy); }
private:
    Image img;
};

//-----------------------------------------------------------------------------

class Image_button_window : public My_window
{
public:
    Image_button_window(Point xy, int w, int h, const string &title,
                        const string& file_name,
                        int r_min = -10, int r_max = 10);

    static constexpr double percent{0.2}; // Процентный множитель
                                          // для построения кнопки
private:
    // Диапазон случайных чисел [r1, r2]
    int r1;
    int r2;
    Image_button ib;

    void rand_move();   // "Случайное" перемещение кнопки
};

//-----------------------------------------------------------------------------

#endif // IMAGE_BUTTON_WINDOW_H
