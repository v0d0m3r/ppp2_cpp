//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

constexpr char fahrenheit = 'f';
constexpr char celsius = 'c';
struct Reading;
const Reading& default_reading();

//------------------------------------------------------------------------------

struct Reading {
    int hour;
    double temperature;
    char kind;
    Reading()
        :hour{default_reading().hour},
         temperature{default_reading().temperature},
         kind{default_reading().kind}
    {}
    Reading(int h, double t, char k)
        :hour{h}, temperature{t}, kind{k}
    { }
};

//------------------------------------------------------------------------------

const Reading& default_reading()
{
    static const Reading reading{0, 0.00, 0};
    return reading;
}

//------------------------------------------------------------------------------
// Ввод из консоли
void fill_from_console(vector<Reading>& temps, const string& invitation_inp)
{
    cout << invitation_inp;
    int hour;
    double temperature;
    char kind;
    for (size_t i=0; i<temps.size(); ++i) {
        cin >> hour >> temperature >> kind;
        if (!cin)
            error("fill_from_console: ", "Не вверный ввод из консоли!");
        if (hour < 0 || 23 < hour)
            error("fill_from_console: ", "Нет такого часа!");
        if (kind!=celsius && kind!=fahrenheit)
            error("fill_from_console: ", "Нет такой еденицы измерения!");
        temps[i] = Reading{hour, temperature, kind};
    }
}

//------------------------------------------------------------------------------
// Вывод в файл
void fill_on_file(const vector<Reading>& temps, const string& name)
{
    ofstream ost {name};    // Поток для записи в файл
    if (!ost) error("невозможно открыть файл: ", name);
    for (const Reading& r : temps)
        ost << r.hour << ' ' << r.temperature
            << r.kind <<'\n';
}

//------------------------------------------------------------------------------

void store_temps()
{
    try {
        const string oname = "./raw_temps.txt";
        constexpr int num_elem = 20;
        const string invitation_inp = "Введите показания час(x) температyра(y)"
                                     " еденица_измерения(c-цельсий, f - фаренгейт)"
                                     " , например, 1 43c, в количестве: 20.\n";
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
    catch(...) {
        cout << "неизвестная ошибка!\n";
    }
}

//------------------------------------------------------------------------------

int main()
{
    store_temps();
    keep_window_open("~~");
    return 0;
}

//------------------------------------------------------------------------------
