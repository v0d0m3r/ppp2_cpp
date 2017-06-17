//-----------------------------------------------------------------------------

#include "Common_window.hpp"

//-----------------------------------------------------------------------------

using namespace Graph_lib;

//-----------------------------------------------------------------------------

Action_window::Action_window(Point xy, int w, int h,
                                         const string& title)
    : Graph_lib::Window(xy, w, h, title),
      start_button{Point{x_max()-230, 0}, 70, 20, "Start",
                   [] (Address, Address pw)
                      {
                           reference_to<Action_window>(pw).start_pressed();
                      }},
      stop_button {Point{x_max()-150, 0}, 70, 20, "Stop",
                   [] (Address, Address pw)
                      {
                          reference_to<Action_window>(pw).stop_pressed();
                      }},
      quit_button {Point{x_max()-70, 0}, 70, 20, "Quit",
                   [] (Address, Address pw)
                      {
                          reference_to<Action_window>(pw).quit_pressed();
                      }}
{
    attach(start_button);
    attach(stop_button);
    attach(quit_button);
}

//-----------------------------------------------------------------------------

void Action_window::timeout_end()
{
    do_action();
    redraw();
    repeat_timeout(t, cb_timeout, this);
}

//-----------------------------------------------------------------------------

void Action_window::start_pressed()
{
    if (status) return; // Часы уже запущены

    status = true;
    add_timeout(t, cb_timeout, this);
}

//-----------------------------------------------------------------------------

void Action_window::stop_pressed()
{
    if (!status) return; // Часы уже остановлены

    status = false;
    remove_timeout(cb_timeout);
}

//-----------------------------------------------------------------------------

void Action_window::cb_timeout(Address pw)
{
    reference_to<Action_window>(pw).timeout_end();
}

//-----------------------------------------------------------------------------

