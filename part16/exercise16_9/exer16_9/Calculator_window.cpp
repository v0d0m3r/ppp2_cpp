//------------------------------------------------------------------------------

#include "Calculator_window.hpp"

//------------------------------------------------------------------------------

using namespace Graph_lib;
using namespace Calc_lib;

//------------------------------------------------------------------------------

Calculator_window::Calculator_window(Graph_lib::Point xy, int w, int h,
                                     const string &title)
    : Window(xy, w, h, title),
      calculate_button{Point{x_max()-150, 0}, 70, 20, "Calculate",
                       [] (Address, Address pw)
                          {
                              reference_to<Calculator_window>(pw).calculate();
                          }
                      },
      quit_button{Point{x_max()-70, 0}, 70, 20, "Quit",
                  [] (Address, Address pw)
                     {
                         reference_to<Calculator_window>(pw).quit();
                     }
                 },
      statement_in {Point{0, 0}, x_max()-160, 40, ""},
      statement_out{Point{0, 80}, x_max()-160, 40, ""}
{
      attach(calculate_button);
      attach(quit_button);

      attach(statement_in);
      attach(statement_out);

}

//------------------------------------------------------------------------------

void prepare_result(const string& src, string& dest)
{
    const string space{"    "};
    dest = "";

    istringstream is{src};
    char ch;
    while (is.get(ch)) {
        if (ch == '\n') dest += space;
        else dest.push_back(ch);
    }
}

//------------------------------------------------------------------------------

void Calculator_window::calculate()
{
    istringstream is{statement_in.get_string()};
    ostringstream os;

    Calculator c{is, os};
    c.calculate();

    string res;
    prepare_result(os.str(), res);

    statement_out.put(res);
    redraw();
}

//------------------------------------------------------------------------------
