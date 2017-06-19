#ifndef CALCULATOR_WINDOW_HPP
#define CALCULATOR_WINDOW_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/GUI.h"
#include "Calculator.hpp"

//------------------------------------------------------------------------------

class Calculator_window : public Graph_lib::Window
{
public:
    Calculator_window(Graph_lib::Point xy, int w, int h,
                      const string& title);
private:
    // Виджеты
    Graph_lib::Button calculate_button; // Рассчитывает инструкцию
    Graph_lib::Button quit_button;      // Завершает работу программы

    Graph_lib::In_box statement_in;
    Graph_lib::Out_box statement_out;

    void calculate();
    void quit() { hide(); }
};

//------------------------------------------------------------------------------

#endif // CALCULATOR_WINDOW_HPP
