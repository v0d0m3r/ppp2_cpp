#ifndef ANALOG_CLOCK_WINDOW_HPP
#define ANALOG_CLOCK_WINDOW_HPP

//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/Common_window.hpp"

//-----------------------------------------------------------------------------

struct Analog_clock_window : public Action_window
{
    Analog_clock_window(Graph_lib::Point xy, int w, int h,
                        const string& title);
protected:
    void do_action() override { aclock.update(); }

private:    
    // Виджеты
    Graph_lib::Analog_clock aclock;
};

//-----------------------------------------------------------------------------

#endif // ANALOG_CLOCK_WINDOW_HPP
