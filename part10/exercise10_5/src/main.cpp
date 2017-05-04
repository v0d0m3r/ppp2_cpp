//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

const int not_a_reading = -7777;    // Ниже абсолютного нуля
const int not_a_month = -1;

//------------------------------------------------------------------------------

struct Day {
    vector <double> hour {vector<double>(24, not_a_reading)};
};

//------------------------------------------------------------------------------

struct Month {
    int month {not_a_month};
    vector<Day> day{32};
};

//------------------------------------------------------------------------------

struct Year {
    int year;
    vector<Month> month{12};
};

//------------------------------------------------------------------------------

struct Reading {
    int day;
    int hour;
    double temperature;
};

//------------------------------------------------------------------------------

istream& operator>>(istream& is, Reading& r)
{
    char ch1;
    if (is >> ch1 && ch1 != '(') {  // Может ли это быть Reading
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }
    char ch2;
    int d;
    int h;
    double t;
    is >> d >> h >> t >> ch2;
    if (!is || ch2 != ')')  error("Плохая запись");
    r.day = d;
    r.hour = h;
    r.temperature = t;
    return is;
}

//------------------------------------------------------------------------------

vector<string> month_input_tb1= {
    "jan", "feb", "mar", "apr", "may", "jun",
    "jul", "aug", "sep", "oct", "nov", "dec"
};

//------------------------------------------------------------------------------

int month_to_int(const string& s)
{     
    for (size_t i=0; i < month_input_tb1.size(); ++i)
        if (s == month_input_tb1[i]) return i;
    return -1;
}

//------------------------------------------------------------------------------

string int_to_month(int m)
{
    // месяц от 0 до 11
    if (m<0 || m > 11) error("int_to_month: ", "неправильный индекс месяца");
    return month_input_tb1[m];
}

//------------------------------------------------------------------------------

void end_of_loop(istream& ist, char term, const string& message)
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

constexpr int implausible_min = -200;
constexpr int implausible_max = 200;

//------------------------------------------------------------------------------

bool is_valid(const Reading& r)
{
    if (r.day <1 || 31<r.day) return false;
    if (r.hour<0 || 23<r.hour) return false;
    if (r.temperature < implausible_min
        || r.temperature > implausible_max)
        return false;
    return true;
}

//------------------------------------------------------------------------------

istream& operator>>(istream& is, Month& m)
// Считаем объект класса Month из потока is в объект m
// Формат: { month feb ... }
{
    char ch = 0;
    if (is >> ch && ch != '{') {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    string month_marker;
    string mm;
    is >> month_marker >> mm;
    if (!is || month_marker != "month")
        error("неправильное начало Month");
    m.month = month_to_int(mm);

    int duplicates = 0;
    int invalids = 0;
    for (Reading r; is >> r;) {
        if (is_valid(r)) {
            if (m.day[r.day].hour[r.hour] != not_a_reading)
                ++duplicates;
            m.day[r.day].hour[r.hour] = r.temperature;
        }
        else
            ++invalids;
    }
    ostringstream ss;
    ss << invalids;
    if (invalids)
        error("неправильные данные в Month, всего: ", ss.str());
    ss << duplicates;
    if (duplicates)
        error("Повторяющиеся показания в Month, всего: ", ss.str());
    end_of_loop(is, '}', "Неправильный конец Month");
    return is;
}

//------------------------------------------------------------------------------

istream& operator>>(istream& is, Year& y)
// Считаем объект класса Month из потока is в объект m
// Формат: { year 1972 ... }
{
    char ch = 0;
    is >> ch;
    if (ch != '{') {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    string year_marker;
    int yy;
    is >> year_marker >> yy;
    if (!is || year_marker != "year")
        error("неправильное начало Year");
    y.year = yy;
    for (Month m; is >> m;) {
        y.month[m.month] = m;
        m = Month{};
    }
    end_of_loop(is, '}', "Неправильный конец Year");
    return is;
}

//------------------------------------------------------------------------------

void print_day(ostream& ost, Day& d, int num_day)
{
    char ch1 = '(';
    char ch2 = ')';
    for (size_t i=0; i < d.hour.size(); ++i) {
        if (d.hour[i] != not_a_reading) {
            ost << ch1 << num_day << ' '
                << i << ' ' << d.hour[i]
                << ch2 << ' ';
        }
    }

}

//------------------------------------------------------------------------------

void print_month(ostream& ost, Month& m)
{
    string month_marker = "month";
    char ch1 = '{';
    char ch2 = '}';
    ost << ch1 << ' ' << month_marker
        << ' ' << int_to_month(m.month) << ' ';
    // Day с 1 по 31 элемент
    for (size_t i = 1; i < m.day.size(); ++i)
        print_day(ost, m.day[i], i);
    ost << ch2 << ' ';

}

//------------------------------------------------------------------------------

void print_year(ostream& ost, Year& y)
{
    string year_marker = "year";
    char ch1 = '{';
    char ch2 = '}';
    ost << ch1 << ' ' << year_marker
        << ' ' << y.year << ' ';

    for (size_t i = 0; i < y.month.size(); ++i)
        if (y.month[i].month != not_a_month)
            print_month(ost, y.month[i]);

    ost << ch2 << '\n';
}

//------------------------------------------------------------------------------

void reading_format_file()
{
    try {
        const string iname = "./input_temps.txt";
        const string oname = "./output_temps.txt";
        ifstream ifs{iname};
        if (!ifs)
            error("temp_stats: ", "Невозможно открыть входной файл");
        ifs.exceptions(ifs.exceptions()|ios_base::badbit);
        ofstream ofs{oname};
        if (!ofs)
            error("temp_stats: ", "Невозможно открыть выходной файл");

        vector<Year> ys;
        Year y;
        while (true) {
             if (!(ifs >> y)) break;
             ys.push_back(y);
             y = Year{};
        }
        cout << "Считано " << ys.size() << " годичных записей\n";
        for (Year& y : ys) print_year(ofs, y);

    }
    catch(exception& e) {
        cout << "ошибка: " << e.what() << '\n';
    }
    catch(...) {
        cout << "неизвестная ошибка\n";
    }
}

//------------------------------------------------------------------------------

int main()
{
    reading_format_file();
    keep_window_open("~~");
    return 0;
}

//------------------------------------------------------------------------------
