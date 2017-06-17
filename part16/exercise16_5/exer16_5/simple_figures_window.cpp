#include "simple_figures_window.h"

//-----------------------------------------------------------------------------

Simple_figures_window::Simple_figures_window(Point xy, int w, int h,
                                             const string &title)
    : Figures_window(xy, w, h, title),
      next_button{Point{x_max()-150, 0}, 70, 20, "Next",
                  [] (Address, Address pw)
                     {
                          reference_to<Simple_figures_window>(pw).next();
                     }
                  }
{
    attach(next_button);
}

//-----------------------------------------------------------------------------

void skip_to_int()
{
    if (cin.fail()) {   // Обнаружено нечто не являющееся
                        // целым числом
        cin.clear();    // Возвращаем поток в состояние good
        for (char ch; cin >> ch;) { // Отбрасываем не цифры
            if (isdigit(ch) || ch == '-') {
                cin.unget();    // Возвращаем цифру в поток, чтобы
                                // можно было считать число
                return;
            }
        }
    }
    error("Ввода нет!");
}

//-----------------------------------------------------------------------------

int get_int()
{
    int n = 0;
    while(true) {
        if (cin >> n) return n;
        cout << "Это не число; попробуйте ещё раз\n";
        skip_to_int();
    }
}

//-----------------------------------------------------------------------------

int get_int(int low, int high,
            const string& greeting,
            const string& sorry)
{
    cout << greeting << ": [" << low << ';' << high << "]\n";
    while (true) {
        int n = get_int();
        if (low<=n && n<=high) return n;
        cout << sorry << ": [" << low << ';' << high << "]\n";
    }
}

//-----------------------------------------------------------------------------

void Simple_figures_window::next()
{
    int x_coord = get_int(0, x_max(),
                          "Введите значение координаты х",
                          "Вне диапазона, повторите еще");
    int y_coord = get_int(0, y_max(),
                          "Введите значение координаты y",
                          "Вне диапазона, повторите еще");
    current_shape().move(x_coord, y_coord);
    redraw();
}

//-----------------------------------------------------------------------------
