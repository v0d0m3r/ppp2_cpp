/*//------------------------------------------------------------------------------

#include "Table_file.hpp"

//------------------------------------------------------------------------------

Table_file::Table_file(const string& n)
    // Открывает файл с именем n
    // Считывает строки из файла в n
    // Находит в lines сообщения и помещает их в m;
    // для простоты полагаем, что каждое сообщение
    // заканчивается строкой "----"
{
    ifstream in{n};   // Входной файл
    if (!in) error("Нет входного файла\n");

    string line;                // Входной буфер
    int lineno{0};

    regex header{R"(^[\w ]+(\s+[\w ]+)*$)"};
    regex row{R"(^([\w ]+)(\s+\d+)(\s+\d+)(\s+\d+)$)"};

    if (getline(in, line)) {    // Проверка заголовка
        smatch matches;
        if (!regex_match(line, matches, header))
            error("нет заголовка");
    }

    // Итог по столбцам
    int boys{0};
    int girls{0};

    int curr_boy{0};
    int curr_girl{0};

    while (getline(in, line)) { // Проверка данных
        ++lineno;
        smatch matches;
        if (!regex_match(line, matches, row))
            error("неверная строка ", to_string(lineno));

        // Проверка строки
        curr_boy   = m_to<int>(matches[1]);
        curr_girl  = m_to<int>(matches[2]);
        int curr_total = m_to<int>(matches[3]);

        if (curr_boy+curr_girl != curr_total)
            error("Неверная сумма в строке\n");

        if ((in >> ws).eof())   // Внимание! Съедает пробельные
            break;              // символы, определяет последнюю строку

        // Обновление итоговых значений
        boys  += curr_boy;
        girls += curr_girl;
    }

    if (curr_boy != boys)
        error("Количество мальчиков не сходится\n");
    if (curr_girl != girls)
        error("Количество девочек не сходится\n");
}

//------------------------------------------------------------------------------

bool find_from_addr(const Message* m, string& s)
{
    if (m == nullptr)
        throw runtime_error{"Bad message"};

    for (const auto& x : *m)
        if (int n = is_prefix(x, "From: ")) {
            s = string(x, n);
            return true;
        }
    return false;
}

//------------------------------------------------------------------------------

bool find_subject(const Message* m, string& s)
{
    if (m == nullptr)
        throw runtime_error{"Bad message"};

    for (const auto& x : *m)
        if (int n = is_prefix(x, "Subject: Re: ")){
            s = string(x, n);
            return true;
        }
        else if (int n = is_prefix(x, "Subject: ")) {
            s = string(x, n);
            return true;
        }

    return false;
}

//------------------------------------------------------------------------------
*/
