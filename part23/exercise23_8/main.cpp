//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

// Получает из входного потока шаблон и имя файла;
// проверяет шаблон и ищет строки в файле, содержащие его
void exercise23_8()
{
    regex pattern;

    string pat;
    cout << "введите шаблон: ";
    getline(cin, pat);          // Считываем шаблон

    string fname;
    cout << "введите имя файла: ";
    getline(cin, fname);        // Считываем имя файла

    ifstream in{fname};
    if (!in) error("Не удалось открыть файл" + fname);

    try {
        pattern = pat;          // Проверка шаблона
        cout << "шаблон: " << pat << '\n';
    }
    catch (bad_exception) {
        cout << "Не корректное выражение: " << pat << '\n';
        exit(1);
    }

    int lineno{0};
    for (string line; getline(in, line); ) {
        ++lineno;
        smatch matches;
        if (regex_search(line, matches, pattern))
            cout << lineno << ": " << matches[0] << '\n';
    }
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise23_8();
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
