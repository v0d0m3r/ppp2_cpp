#ifndef ANALOG_CLOCK_WINDOW_HPP
#define ANALOG_CLOCK_WINDOW_HPP

//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/GUI.h"

//-----------------------------------------------------------------------------

using namespace Graph_lib;

//-----------------------------------------------------------------------------

class Analog_clock_window : public Graph_lib::Window
{
public:
    Analog_clock_window(Point xy, int w, int h, const string& title);

private:    
    static constexpr double t{0.5};
    bool status{false};    

    // Виджеты
    Analog_clock aclock;
    Button start_button; // Запускает часы
    Button stop_button;  // Останавливает часы
    Button quit_button;  // Завершает работу программы

    void timeout_end();

    // Действия
    void start_pressed();
    void stop_pressed();
    void quit_pressed() { hide(); }

    // Callback-функции
    static void cb_timeout(Address);   
};

//-----------------------------------------------------------------------------

#endif // ANALOG_CLOCK_WINDOW_HPP
