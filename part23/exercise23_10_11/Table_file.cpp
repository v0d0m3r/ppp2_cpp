//------------------------------------------------------------------------------

#include "Table_file.hpp"

//------------------------------------------------------------------------------

Table_file::Table_file(const string& n)
    // Открывает файл с именем n
    // Считывает строки из файла в n
{
    ifstream in{n};   // Входной файл
    if (!in) throw Bad_table_file{"Не удалось открыть файл: " + n};

    string line;                // Входной буфер
    int lineno{0};

    regex header{R"(^[\w ]+(\s+[\w ]+)*$)"};
    regex row{R"(^[\w ]+(\s+\d+)(\s+\d+)(\s+\d+)$)"};

    if (getline(in, line)) {    // Проверка заголовка
        smatch matches;
        if (!regex_match(line, matches, header))
            throw Bad_table_file{"нет заголовка"};
    }
    lines.push_back(line);

    // Итог по столбцам
    int boys{0};
    int girls{0};

    while (getline(in, line)) { // Проверка данных
        ++lineno;
        smatch matches;
        if (!regex_match(line, matches, row))
            throw Bad_table_file{"неверная строка " + to_string(lineno)};

        // Проверка строки
        int curr_boy   = m_to<int>(matches[1]);
        int curr_girl  = m_to<int>(matches[2]);
        int curr_total = m_to<int>(matches[3]);

        if (curr_boy+curr_girl != curr_total)
            throw Bad_table_file{"Неверная сумма в строке"};

        lines.push_back(line);

        if ((in >> ws).eof()) { // Внимание! Съедает пробельные
                                // символы, определяет последнюю строку
            if (curr_boy != boys)
                throw Bad_table_file{"Количество мальчиков не сходится"};
            if (curr_girl != girls)
                throw Bad_table_file{"Количество девочек не сходится"};
            break;
        }

        // Обновление итоговых значений
        boys  += curr_boy;
        girls += curr_girl;
    }
    auto p{lines.begin()};
    ++p;
    body = Body{p, lines.end()};
}

//------------------------------------------------------------------------------
