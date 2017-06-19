//------------------------------------------------------------------------------

#include "Calculator_window.hpp"

//------------------------------------------------------------------------------

int main()
{
    Calculator_window cw{Graph_lib::Point{100, 100}, 600, 400, "Calculator"};
    return Graph_lib::gui_main();

    /*Calc_lib::Calculator c{cin, cout};
    c.calculate();*/

    return 0;
}

//------------------------------------------------------------------------------
