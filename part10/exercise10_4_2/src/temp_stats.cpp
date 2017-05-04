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
// print_reading_tb() печатает элементы массива
void print_reading_tb(const vector<Reading>& temps)
{
    for (const Reading& t:temps)
        cout << "Час: " << t.hour
             << "; Температура: "
             << t.temperature << t.kind <<'\n';
}

//------------------------------------------------------------------------------

void celsius_to_fahrenheit(Reading& r)
{
    if (r.kind == celsius) {
        r.kind = fahrenheit;
        r.temperature = 9.0*r.temperature/5 + 32;
    }
}

//------------------------------------------------------------------------------

void end_of_loop(ifstream& ist, char term, const string& message)
{
    if (ist.eof()) {        // Конец файла
        ist.clear();
        return;
    }
    if (ist.fail()) {
        ist.clear();
        char c;
        if (ist >> c && c==term) return;
        error("end_of_loop: ", message);
    }
}

//------------------------------------------------------------------------------

void fill_from_file(ifstream& ist, vector<Reading>& temps, char terminator)
{
    int hour;
    double temperature;
    char kind;
    while (ist >> hour >> temperature >> kind) {
        if (hour < 0 || 23 < hour)
            error("fill_from_console: ", "Нет такого часа!");
        if (kind!=celsius && kind!=fahrenheit)
            error("fill_from_console: ", "Нет такой еденицы измерения!");
        Reading reading{hour, temperature, kind};
        celsius_to_fahrenheit(reading);
        temps.push_back(reading);
    }
    end_of_loop(ist, terminator, "Неправильное завершение файла");
}

//------------------------------------------------------------------------------

double calc_mid_value(const vector<Reading>& temps)
{
    if (temps.size()==0)
        error("calc_mid_value: ", "Пустые показания температуры!");
    double sum = 0.00;
    for (const Reading& t:temps)
        sum+=t.temperature;
    double mid_val = sum*1.00/temps.size();
    return mid_val;
}

//------------------------------------------------------------------------------

bool compare_by_temp(const Reading& a, const Reading& b)
{
    return a.temperature < b.temperature;
}

//------------------------------------------------------------------------------

double calc_mediana(vector<Reading> temps)
{
    double mediana = 0.00;
    sort(temps.begin(), temps.end(), compare_by_temp);
    int remmainder_temps = temps.size() % 2;
    int half_elem = 0;
    if (remmainder_temps==0) {
        half_elem = temps.size()/2;
        double value1 = temps[half_elem].temperature;
        double value2 = temps[half_elem+1].temperature;
        mediana = (value1 + value2)*1.0/2;

    }
    else {
        int half_elem = temps.size()/2;
        ++half_elem;
        mediana = temps[half_elem].temperature;
    }
    return mediana;
}

//------------------------------------------------------------------------------

void temp_stats()
{
    try {
        const string iname = "./raw_temps.txt";
        // Показания температур
        vector<Reading> temps;
        ifstream ist{iname};
        if (!ist)
            error("temp_stats: ", "Невозможно открыть входной файл");
        ist.exceptions(ist.exceptions()|ios_base::badbit);

        char term = '*';                     // Символ прекращения ввода
        fill_from_file(ist, temps, term);    // Ввод из файла        
        print_reading_tb(temps);
        cout << "Среднее значение температуры: "
             << calc_mid_value(temps) << '\n';
        cout << "Медиана: "
             << calc_mediana(temps) << '\n';
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
    temp_stats();
    keep_window_open("~~");
    return 0;
}

//------------------------------------------------------------------------------
