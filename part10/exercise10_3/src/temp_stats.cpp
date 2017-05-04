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
// print_reading_tb() печатает элементы массива
void print_reading_tb(const vector<Reading>& temps)
{
    for (const Reading& t:temps)
        cout << "Час: " << t.hour
             << "; Температура: " << t.temperature << '\n';
}

//------------------------------------------------------------------------------

void fill_from_file(ifstream& ist, vector<Reading>& temps, char terminator)
{
    int hour;
    double temperature;
    while (ist >> hour >> temperature) temps.push_back(Reading{hour, temperature});
    if (ist.eof()) {        // Конец файла
        ist.clear();
        return;
    }
    ist.clear();            // Возвращаем в состояние good

    char c;
    ist >> c;               // Чтение символа(если повезет -
                            // символа завершения)
    if (c != terminator) {  // Неожиданный символ
        ist.unget();        // Вернуть его в поток
        ist.clear(ios_base::failbit);   // Вернуть в состояние fail
    }
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
        ist.exceptions(ist.exceptions()|ios_base::badbit);
        if (!ist)
            error("temp_stats: ", "Невозможно открыть входной файл");
        char term = '*';                     // Символ прекращения ввода
        fill_from_file(ist, temps, term);    // Ввод из файла
        if (!ist) error("temp_stats: ", "Ошибка формата");
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
