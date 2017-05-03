//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

void fill_from_file(ifstream& ist, vector<int>& integers, char terminator)
{
    for (int i; ist >> i;) integers.push_back(i);
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

void sum_calculate(const string& fname)
try {
    vector<int> integers;
    ifstream ist{fname};
    ist.exceptions(ist.exceptions()|ios_base::badbit);
    if (!ist)
        error("sum_calculate: ",
              "Невозможно открыть входной файл");
    char term = '*';                        // Символ прекращения ввода
    fill_from_file(ist, integers, term);    // Ввод из файла
    if (!ist)
        error("sum_calculate: ", "Ошибка формата");
    int sum = 0;
    for (int i : integers)                  // Расчет суммы чисел из файла
            sum+=i;
    cout << sum << '\n';
}
catch(exception& e) {
    cout << "ошибка: " << e.what() << '\n';
}

//------------------------------------------------------------------------------

int main()
try {
    const string fname = "./mydata.txt";
    sum_calculate(fname);
    keep_window_open("~~");
    return 0;
}
catch(...) {
    cout << "Неизвестная ошибка!\n";
}

//------------------------------------------------------------------------------
