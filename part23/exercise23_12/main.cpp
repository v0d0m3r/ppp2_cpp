//------------------------------------------------------------------------------

#include "../example23/Mail_file.hpp"

//------------------------------------------------------------------------------

// Регулярные выражения описывают дату
// Для простоты в понятие год заложены 4 цифры
const vector<regex>& regex_tb()
{
    static vector<regex> vr {
        regex{R"(([12]\d|3[01]|0?[1-9])[\.\\\s/\-]+(0?[1-9]|1[0-2])[\.\\\s/\-]+(\d{4}))"},
        regex{R"((\d{4})[\.\\\s/]+(0?[1-9]|1[0-2])[\.\\\s/]+([12]\d|3[01]|0?[1-9]))"},
        regex{R"((\d{4})[\.\\\s/\-]+([a-zA-Z]{3})[\.\\\s/\-]+([12]\d|3[01]|0?[1-9]))"},
        regex{R"(([12]\d|3[0-1]|0?[1-9])[\.\\\s/\-]+([a-zA-Z]{3})[\.\\\s/\-]+(\d{4}))"}
    };
    return vr;
}

//------------------------------------------------------------------------------

enum class Month {
    jan=1, feb, mar, apr, may, jun,
    jul, aug, sep, oct, nov, dec
};

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, Month m)
{
    return os << int(m);
}

//------------------------------------------------------------------------------

const map<string, Month>& month_tb()
{
    static map<string, Month> vr {
        {"jan", Month::jan}, {"Jan", Month::jan},
        {"feb", Month::feb}, {"Feb", Month::feb},
        {"mar", Month::mar}, {"Mar", Month::mar},
        {"apr", Month::apr}, {"Apr", Month::apr},
        {"may", Month::may}, {"May", Month::may},
        {"jun", Month::jun}, {"Jun", Month::jun},
        {"jul", Month::jul}, {"Jul", Month::jul},
        {"aug", Month::aug}, {"Aug", Month::aug},
        {"sep", Month::sep}, {"Sep", Month::sep},
        {"oct", Month::oct}, {"Oct", Month::oct},
        {"nov", Month::nov}, {"Nov", Month::nov},
        {"dec", Month::dec}, {"Dec", Month::dec}
    };
    return vr;
}

//------------------------------------------------------------------------------

inline bool is_year(const string& str)
{   // Годом являются любые 4 цифры
    if (str.size() == 4) return true;
    return false;
}

//------------------------------------------------------------------------------

// Проверка является m месяцем
inline bool is_valid_month(const string& m)
{
    if (m.size() < 3) return true;
    const auto& months{month_tb()};
    auto mon{months.find(m)};
    if (mon == months.end()) return false;
    return true;
}

//------------------------------------------------------------------------------

string get_month_iso(const string& m)
{
    ostringstream os;
    if (m.size() < 3) {
        if (m.size() == 1) os << 0 << m;
        else               os << m;
        return os.str();
    }

    const auto& months{month_tb()};
    auto mon{months.find(m)};
    if (mon == months.end()) error("bad month");
    if (int(mon->second) < 10) os << 0 << mon->second;
    else                       os << mon->second;
    return os.str();
}

//------------------------------------------------------------------------------

string get_day_iso(const string& d)
{    
    int day{m_to<int>(d)};
    if (day > 31 && day < 1) error("Bad day");

    ostringstream os;
    if (day < 10)  // Добавляем leading zero
        os << 0 << day;
    else
        return d;
    return os.str();
}

//------------------------------------------------------------------------------

// Переводит все даты, соответствующие regex_tb
// в iso yyyy-mm-dd формат
void exercise23_12()
{
    ifstream in{"./file"};
    if (!in) error("Нет файла");

    ofstream out{"./file.out"};
    const auto& regextb{regex_tb()};   
    for (string line; getline(in, line); ) {        
        smatch matches;
        for (const auto& r : regextb) {      // Рассматриваем все шаблоны
            // Ищем первое совпадение
            if (!regex_search(line, matches, r)) continue;

            // Обрабатываем совпадения
            string suffix{line};
            line.clear();
            while (regex_search(suffix, matches, r)) {
                line += matches.prefix().str();

                if (     !is_valid_month(matches[2]))
                    line += to_string(matches[0]);
                else if (is_year(matches[1]))
                    line += to_string(matches[1])
                            + '-' + get_month_iso(to_string(matches[2]))
                            + '-' + get_day_iso(to_string(matches[3]));
                else
                    line += to_string(matches[3])
                            + '-' + get_month_iso(to_string(matches[2]))
                            + '-' + get_day_iso(to_string(matches[1]));
                suffix = matches.suffix().str();
            }
            line += suffix;
        }
        out << line << '\n';
    }
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise23_12();
    return 0;
}
catch (const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "oops!";
    return -2;
}

//------------------------------------------------------------------------------
