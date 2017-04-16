//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//-----------------------------------------------------------------------------

double square(double x)
{
    return x*x;
}

//-----------------------------------------------------------------------------
// Находит и выводит корни
// квадратного уравнения
void view_result(double a, double b, double c)
{
    if (a == 0)
        error("Ошибка: Это неквадратное уравнение!");

    double discr = square(b)-4*a*c; // Находим дискриминант
    double root1 = 0;               // Корень уравнения
    double root2 = 0;

    if (discr < 0)
        error("Ошибка: Нет вещественных корней!");
    else if (discr == 0) {          // Два одинаковых корня
        cout << "Два одинаковых корня!!!\n";
        root1 = -b / (2*a);
        root2 = root1;
    }
    else if (discr > 0) {
        root1 = (-b+sqrt(discr))/(2*a);
        root2 = (-b-sqrt(discr))/(2*a);
    }
    else
        error("Неизвестная ошибка!");

    cout << "Корень №1: " << root1 << '\n'
         << "Корень №2: " << root2 << '\n';
    return;
}

//-----------------------------------------------------------------------------

int main()
try {
    cout << "Квадратное уравнение представлено: "
            "a*x^2 + b*x + c = 0.\n"
            "Введите a, b, и c:\n";

    double a = 0;
    double b = 0;
    double c = 0;

    cin >> a >> b >> c;
    if (!cin) error("Не могу считать коффициенты!");

    view_result(a,b,c);

    keep_window_open();
    return 0;
}
catch (exception& e) {
    cerr << e.what() << '\n';
    keep_window_open();
    return -1;
}
catch (...) {
    cerr << "exiting\n";
    keep_window_open();
    return -2;
}

//-----------------------------------------------------------------------------
