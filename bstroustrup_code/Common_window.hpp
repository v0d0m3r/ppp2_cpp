#ifndef COMMON_WINDOW_HPP
#define COMMON_WINDOW_HPP

//-----------------------------------------------------------------------------

#include "GUI.h"

//-----------------------------------------------------------------------------
// Окно, в котором выполняется какое-либо
// действие/я по таймауту
class Action_window : public Graph_lib::Window
{
public:
    Action_window(Graph_lib::Point xy, int w, int h,
                  const string& title);

    double frequency() const { return t; }
    void set_frequency(double tt)
    {
        if (tt < 0) error("set_frequency: invalid value");
        t = tt;
    }

    Action_window(const Action_window&) = delete;
    Action_window& operator=(const Action_window&) = delete;

protected:
    virtual void do_action() = 0;

private:
    double t{0.5};          // Частота/время повторений
    bool status{false};

    // Виджеты
    Graph_lib::Button start_button; // Запускает цикл выполнения действий
    Graph_lib::Button stop_button;  // Останавливает
    Graph_lib::Button quit_button;  // Выход

    void timeout_end();

    // Действия
    void start_pressed();
    void stop_pressed();
    void quit_pressed() { hide(); }

    // Callback-функции
    static void cb_timeout(Graph_lib::Address);
};

//-----------------------------------------------------------------------------

#endif // COMMON_WINDOW_HPP
