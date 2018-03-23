//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

const vector<regex>& regex_tb()
{
    static vector<regex> vr {
        regex{R"(([12]\d|0?[1-9]|3[01])[\.\\\s/\-]+(0?[1-9]|1[0-2])[\.\\\s/\-]+(\d{4}))"},
        regex{R"((\d{4})[\.\\\s/]+(0?[1-9]|1[0-2])[\.\\\s/]+([12]\d|0?[1-9]|3[01]))"},
        regex{R"((\d{4})[\.\\\s/\-]+([a-zA-Z]{3})[\.\\\s/\-]+([12]\d|0?[1-9]|3[0-1]))"},
        regex{R"(([12]\d|0?[1-9]|3[0-1])[\.\\\s/\-]+([a-zA-Z]{3})[\.\\\s/\-]+(\d{4}))"}
    };
    return vr;
}

//------------------------------------------------------------------------------

enum class Month {
    jan=1, feb, mar, apr, may, jun,
    jul, aug, sep, oct, nov, dec
};

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

bool is_year(const string& str)
{
    if (str.size() == 4)
        return true;
    return false;
}

//------------------------------------------------------------------------------

void exercise23_12()
{
    ifstream in{"./file"};
    if (!in) error("Нет файла");

    ofstream out{"./file.out"};

    const auto& regextb{regex_tb()};
    int lineno{0};
    for (string line; getline(in, line); ) {
        ++lineno;
        smatch matches;
        for (const auto& r : regextb) {      // Рассматриваем все шаблоны
            // Ищем первое совпадение
            if (regex_search(line, matches, r))
                cout << lineno << ": " << matches[0] << '\n';
            else
                continue;

            // Ищем остальные совпадения
            for (string suffix{matches.suffix().str()};
                 regex_search(suffix, matches, r);
                 suffix = matches.suffix().str())
                cout << lineno << ": " << matches[0] << '\n';
        }
    }
}

//------------------------------------------------------------------------------

int main()
try
{
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
