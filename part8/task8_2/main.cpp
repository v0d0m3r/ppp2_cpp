//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

void swap_v(int a, int b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

//------------------------------------------------------------------------------

void swap_r(int& a, int& b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

//------------------------------------------------------------------------------

int main()
{
    int x = 7;
    int y = 9;
    swap_v(x, y);
    cout << "swap_v(x,y): " << x << '\t' << y << '\n';
    swap_r(x, y);
    cout << "swap_r(x,y): " << x << '\t' << y << '\n';
    const int cx = 7;
    const int cy = 9;
    swap_v(cx, cy);
    cout << "swap_v(cx,cy): " << cx << '\t' << cy << '\n';
    /* Ошибка: попытка изменить значение
    * постоянной переменной
    * swap_r(cx,cy);
    * cout << "swap_r(cx,cy): " << cx << '\t' << cy << '\n';
    * swap_r(7.7, 9.9);
    */
    swap_v(7.7, 9.9);
    cout << "swap_v(7.7, 9.9): " << cx << '\t' << cy << '\n';
    double dx = 7.7;
    double dy = 9.9;
    swap_v(dx, dy);
    cout << "swap_v(dx, dy): " << dx << '\t' << dy << '\n';
    /* Ошибка: Попытка присвоить ссылки
    * имя пременной другого типа
    * swap_r(dx, dy);
    cout << "swap_r(dx, dy): " << dx << '\t' << dy << '\n';*/

    keep_window_open("~~");
    return 0;
}

//------------------------------------------------------------------------------

