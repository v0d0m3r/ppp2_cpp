//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

using Kind_of_ncards = vector<pair<string, regex>>;

//------------------------------------------------------------------------------

const Kind_of_ncards& alternative_regex_tb()
{
    static const Kind_of_ncards m {
        make_pair("visa", regex{R"(\b4[\s\-]*(?:\d[\s\-]*){12})"
                                R"((?:(?:\d[\s\-]*){3})?\b)"}),
        make_pair("mstr",
                  regex{R"(\b(?:5[\s\-]*[1-5][\s\-]*(?:\d[\s\-]*){2})"
                        R"(|(?:2[\s\-]*){3}[1-9])"
                        R"(|(?:2[\s\-]*){2}[3-9][\s\-]*\d[\s\-]*)"
                        R"(|2[\s\-]*[3-6][\s\-]*(?:\d[\s\-]*){2})"
                        R"(|2[\s\-]*7[\s\-]*[01][\s\-]*\d[\s\-]*)"
                        R"(|2[\s\-]*7[\s\-]*2[\s\-]*0[\s\-]*))"
                        R"((?:\d[\s\-]*){12}\b)"}),
        make_pair("all", regex{R"((?:\d[\s\-]*){13})"
                               R"((?:(?:\d[\s\-]*){3})?)"})
    };
    return m;
}

//------------------------------------------------------------------------------

const Kind_of_ncards& ncard_regex_tb()
{
    static const Kind_of_ncards m {
        make_pair("visa", regex{R"(^4\d{12}(?:\d{3})?$)"}),
        make_pair("mstr",
                  regex{R"(^(?:5[1-5]\d{2}|222[1-9]|22[3-9]\d)"
                        R"(|2[3-6]\d{2}|27[01]\d|2720))"
                        R"(\d{12}$)"})
    };
    return m;
}

//------------------------------------------------------------------------------

void exercise23_7()
{
    ifstream in{"./file"};                      // Входной файл
    if (!in) cerr << "Нет файла\n";
    // cout << "шаблон: " << pat << '\n';

    const auto& regextb{ncard_regex_tb()};
    int lineno{0};
    regex delim(R"([\s\-]*)");                  // Формат для разделителей
    regex all_card{R"((?:\d[\s\-]*){13})"       // Формат всех карточек
                   R"((?:(?:\d[\s\-]*){3})?)"};
    for (string line; getline(in, line); ) {    // Чтение строки
        ++lineno;
        smatch matches;
        // В строке есть номер кредитки?
        if (regex_search(line, matches, all_card)) {
            // Очищаем номер карточки от разделителей
            string ncard{regex_replace(to_string(matches[0]), delim, "")};
            for (const auto& r : regextb)       // Поддерживается вид карты?
                if (regex_search(ncard, matches, r.second)) {
                    // Полное соответствие
                    cout << "type card: "  << r.first
                         << "\tline num: " << lineno
                         << "\tfind: " << ncard << '\n';
                    break;
                }
        }
    }
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise23_7();
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
