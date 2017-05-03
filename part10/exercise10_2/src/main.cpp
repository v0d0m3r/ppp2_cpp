//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

struct Reading {
    int hour;
    double temperature;
    Reading()
        :hour{Reading{0,0.00}.hour},
         temperature{Reading{0,0.00}.temperature}
    {}
    Reading(int h, double t):hour{h}, temperature{t}
    { }
};

//------------------------------------------------------------------------------
// Ввод из консоли
void fill_from_console(vector<Reading>& temps, const string& invitation_inp)
{
    cout << invitation_inp;
    int hour;
    double temperature;
    for (size_t i=0; i<temps.size(); ++i) {
        cin >> hour >> temperature;
        if (!cin)
            error("fill_from_console: ", "Некорректный ввод из консоли!");
        if (hour < 0 || 23 < hour)
            error("fill_from_console: ", "Нет такого часа!");
        temps[i] = Reading{hour, temperature};
    }
}

//------------------------------------------------------------------------------
// Вывод в файл
void fill_on_file(const vector<Reading>& temps, const string& name)
{
    ofstream ost {name};    // Поток для записи в файл
    if (!ost) error("невозможно открыть файл: ", name);
    for (const Reading& r : temps)
        ost << r.hour << ' ' << r.temperature << '\n';
}

//------------------------------------------------------------------------------

void store_temps()
try {
    const string oname = "./raw_temps.txt";
    constexpr int num_elem = 50;
    const string invitation_inp = "Введите 50 пар: температура часы"
                                  " через пробел\n";
    // Показания температур
    vector<Reading> original_reading(num_elem);
    // Ввод температуры с консоли
    fill_from_console(original_reading, invitation_inp);
    // Вывод в файл
    fill_on_file(original_reading, oname);
}
catch(exception& e) {
    cout << "ошибка: " << e.what() << '\n';
}

//------------------------------------------------------------------------------

int main()
try {
    store_temps();
    keep_window_open("~~");
    return 0;
}
catch(...) {
    cout << "Неизвестная ошибка!\n";
}

//------------------------------------------------------------------------------
