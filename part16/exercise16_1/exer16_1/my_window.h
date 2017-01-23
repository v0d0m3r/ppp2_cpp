#ifndef MY_WINDOW_H
#define MY_WINDOW_H

#include "../../../bstroustrup_code/Simple_window.h"

//-----------------------------------------------------------------------------

class My_window : public Simple_window
{
public:
    My_window(Point xy, int w, int h, const string& title);
private:
    Button quit_button; // Завершает работу программы
    void quit() { hide(); }
};

//-----------------------------------------------------------------------------

#endif // MY_WINDOW_H
