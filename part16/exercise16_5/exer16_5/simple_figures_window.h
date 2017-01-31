#ifndef SIMPLE_FIGURES_WINDOW_H
#define SIMPLE_FIGURES_WINDOW_H

//-----------------------------------------------------------------------------

#include "../../exercise16_4/exer16_4/figures_window.h"

//-----------------------------------------------------------------------------

class Simple_figures_window : public Figures_window
{
public:
    Simple_figures_window(Point xy, int w, int h, const string& title);

private:
    Button next_button;     // Кнопка next

    void next();
};

//-----------------------------------------------------------------------------

#endif // SIMPLE_FIGURES_WINDOW_H
