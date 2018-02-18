//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

const vector<regex>& regex_tb()
{
    static vector<regex> vr {
        regex{R"(([0-2]?[1-9]|3[01])[\.\\\s/\-]+(0?[1-9]|1[0-2])[\.\\\s/\-]+(\d{4}))"},
        regex{R"((\d{4})[\.\\\s/\-]+(0?[1-9]|1[0-2])[\.\\\s/\-]+([0-2]?[1-9]|3[01]))"},
        regex{R"((\d{4})[\.\\\s/\-]+([a-zA-Z]{3})[\.\\\s/\-]+([0-2]?[1-9]|3[0-1]))"},
        regex{R"(([0-2]?[1-9]|3[0-1])[\.\\\s/\-]+([a-zA-Z]{3})[\.\\\s/\-]+(\d{4}))"}
    };
    return vr;
}

//------------------------------------------------------------------------------

void exercise23_6()
{
    ifstream in{"./file"};                   // Входной файл
    if (!in) cerr << "Нет файла\n";
    // cout << "шаблон: " << pat << '\n';

    const auto& regextb{regex_tb()};
    int lineno{0};
    for (string line; getline(in, line); ) { // Чтение строки
        ++lineno;
        smatch matches;
        for (const auto& r : regextb)
            if (regex_search(line, matches, r))
                // Полное соответствие
                cout << lineno << ": " << matches[0] << '\n';
    }
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise23_6();
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
