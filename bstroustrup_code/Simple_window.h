
#include "GUI.h"	// for Simple_window only (doesn't really belong in Window.h)

using namespace Graph_lib;

// Simple_window is basic scaffolding for ultra-simple interaction with graphics
// it provides one window with one "next" button for ultra-simple animation

struct Simple_window : Graph_lib::Window {
	Simple_window(Point xy, int w, int h, const string& title );

    void wait_for_button(); // Простой цикл событий
private:
    Button next_button;     // Кнопка next
    bool button_pushed;     // Деталь реализации
    //static void cb_next(Address, Address); // Обратный вызов
                                             // для кнопки next_button
    void next();            // Действи выполняемое после
                            // щелчка на кнопке next_button
};
