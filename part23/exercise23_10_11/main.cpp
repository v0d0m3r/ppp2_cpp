//------------------------------------------------------------------------------

#include "Table_file.hpp"

//------------------------------------------------------------------------------

struct Row {
    Row() {}
    Row(int b, int g, int t)
        : boy{b}, girl{g}, total{t} {}
    int boy{0};
    int girl{0};
    int total{0};

    Row& operator+=(const Row& rhs)
    {
        boy   += rhs.boy;
        girl  += rhs.girl;
        total += rhs.total;
        return *this; // return the result by reference
    }
};

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Row& r)
{
    return os << r.boy << "\t\t" << r.girl << "\t\t" << r.total;
}

//------------------------------------------------------------------------------

void exercise23_10()
{
    ifstream in{"table.txt"};   // Входной файл
    if (!in) error("Нет входного файла\n");

    string line;                // Входной буфер
    int lineno{0};

    regex header{R"(^[\w ]+(\s+[\w ]+)*$)"};
    regex row{R"(^([\w ]+)(\s+\d+)(\s+\d+)(\s+\d+)$)"};

    string head;
    if (getline(in, line)) {    // Проверка заголовка
        smatch matches;
        if (!regex_match(line, matches, header))
            error("нет заголовка");
        head = line;
    }

    // Итог по столбцам
    int boys{0};
    int girls{0};

    int curr_boy{0};
    int curr_girl{0};
    int curr_total{0};

    map<string, Row> mr;
    string last;

    while (getline(in, line)) { // Проверка данных
        ++lineno;
        smatch matches;
        if (!regex_match(line, matches, row))
            error("неверная строка ", to_string(lineno));

        curr_boy   = m_to<int>(matches[2]);
        curr_girl  = m_to<int>(matches[3]);
        curr_total = m_to<int>(matches[4]);

        regex cls{R"(^\d+)"};
        smatch matches1;
        string cls_str = matches[1];
        if (regex_search(cls_str, matches1, cls))
            cls_str = matches1[0];

        if (curr_boy+curr_girl != curr_total)
            error("Неверная сумма в строке\n");

        if ((in >> ws).eof()) { // Внимание! Съедает пробельные
            last = matches[1];
            break;              // символы, определяет последнюю строку
        }

        Row curr_row{curr_boy, curr_girl, curr_total};
        mr[cls_str] += curr_row;

        // Обновление итоговых значений
        boys  += curr_boy;
        girls += curr_girl;
    }

    if (curr_boy != boys)
        error("Количество мальчиков не сходится\n");
    if (curr_girl != girls)
        error("Количество девочек не сходится\n");

    cout << head << '\n';
    for (const auto& t : mr)
        cout << t.first << "\t\t\t" << t.second << '\n';
    cout << last << "\t\t" << curr_boy << "\t\t" << curr_girl
         << "\t\t" << curr_total << '\n';
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise23_10();
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
