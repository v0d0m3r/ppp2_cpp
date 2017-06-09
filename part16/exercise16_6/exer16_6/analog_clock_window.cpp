//-----------------------------------------------------------------------------

#include "analog_clock_window.hpp"

//-----------------------------------------------------------------------------

Analog_clock_window::Analog_clock_window(Point xy, int w, int h,
                                         const string& title)
    : Graph_lib::Window(xy, w, h, title),
      aclock{Point{x_max()/2, y_max()/2}, 100},
      start_button{Point{x_max()-230, 0}, 70, 20, "Start",
                   [] (Address, Address pw)
                      {
                           reference_to<Analog_clock_window>(pw).start_pressed();
                      }},
      stop_button {Point{x_max()-150, 0}, 70, 20, "Stop",
                   [] (Address, Address pw)
                      {
                          reference_to<Analog_clock_window>(pw).stop_pressed();
                      }},
      quit_button {Point{x_max()-70, 0}, 70, 20, "Quit",
                   [] (Address, Address pw)
                      {
                          reference_to<Analog_clock_window>(pw).quit_pressed();
                      }}
{
    attach(aclock);
    attach(start_button);
    attach(stop_button);
    attach(quit_button);
}

//-----------------------------------------------------------------------------

void Analog_clock_window::timeout_end()
{
    aclock.update();
    redraw();
    repeat_timeout(t, cb_timeout, this);
}

//-----------------------------------------------------------------------------

void Analog_clock_window::start_pressed()
{
    if (status) return; // Часы уже запущены

    status = true;
    add_timeout(t, cb_timeout, this);
}

//-----------------------------------------------------------------------------

void Analog_clock_window::stop_pressed()
{
    if (!status) return; // Часы уже остановлены

    status = false;
    remove_timeout(cb_timeout);
}

//-----------------------------------------------------------------------------

void Analog_clock_window::cb_timeout(Address pw)
{
    reference_to<Analog_clock_window>(pw).timeout_end();
}

//-----------------------------------------------------------------------------
