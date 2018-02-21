//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

template<typename Target, typename Source>
Target m_to(const Source& arg)
{
    stringstream interpreter;
    Target result;
    if (       !(interpreter << arg)    // Запись arg в поток
            || !(interpreter >> result) // Чтение result из потока
            || !(interpreter >> std::ws).eof())
        throw runtime_error{"сбой в to<>()"};
    return result;
}

//------------------------------------------------------------------------------

void exercise23_9()
{
    ifstream in{"table.txt"};   // Входной файл
    if (!in) error("Нет входного файла\n");

    string line;                // Входной буфер
    int lineno{0};

    regex header{R"(^[\w ]+(\t[\w ]+)*$)"};
    regex row{R"(^[\w ]+(   \d+)(   \d+)(   \d+)$)"};

    if (getline(in, line)) {    // Проверка заголовка
        smatch matches;
        if (!regex_match(line, matches, header))
            error("нет заголовка");
    }

    // Итог по столбцам
    int boys{0};
    int girls{0};

    while (getline(in, line)) { // Проверка данных
        ++lineno;
        smatch matches;
        if (!regex_match(line, matches, row))
            error("неверная строка", to_string(lineno));

        if (in.eof()) cout << "Конец файла";

        // Проверка строки
        int curr_boy   = m_to<int>(matches[2]);
        int curr_girl  = m_to<int>(matches[3]);
        int curr_total = m_to<int>(matches[4]);

        if (curr_boy+curr_girl != curr_total)
            error("Неверная сумма в строке\n");

        if (matches[1] == "Alle klasser") { // Последняя строка
            if (curr_boy != boys)
                error("Количество мальчиков не сходится\n");
            if (curr_girl != girls)
                error("Количество девочек не сходится\n");
            if (!(in >> ws).eof())
                error("Символы после последней строки");
            return;
        }
        // Обновление итоговых значений
        boys  += curr_boy;
        girls += curr_girl;
    }
    error("Нет итоговой строки");
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise23_9();
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
