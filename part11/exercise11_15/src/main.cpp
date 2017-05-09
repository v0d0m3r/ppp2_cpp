//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

void end_of_loop(istream& ist, char term, const string& message)
{
    if (ist.eof()) {
        ist.clear();
        return;
    }
    if (ist.fail()) {
        ist.clear();
        char ch;
        if (ist >> ch && ch == term)    return;
        error(message);
    }
}

//------------------------------------------------------------------------------
// По возможности преобразует символы из строки s
// в число с плавающей точкой
double str_to_double(string& s)
{
    istringstream is{s};  // Создаем поток ввода из строки s
    double d;
    is >> d;
    if (!is) error("Ошибка формата типа int: ", s);
    return d;
}

//------------------------------------------------------------------------------
// Заполняет вектор из потока ввода
void fill_vector(istream& ist, vector<double>& digits,
                 char term, const string& message)
{
    for (string s; ist >> s; )
        digits.push_back(str_to_double(s));
    end_of_loop(ist, term, message);
}

//------------------------------------------------------------------------------

void fill_on_stream(ostream& ost, const vector<double>& digits)
{
    constexpr int max_dig = 4;      // Возможное количество
                                    // чисел в строке
    int current_dig = 0;
    ost << scientific << setprecision(8);
    for (size_t i=0; i < digits.size(); ++i) {
        if (current_dig == max_dig) {  // Конец строки
            ost << '\n';
            current_dig = 0;
        }
        ost << setw(20) << digits[i] << '|';
        ++current_dig;
    }
    ost << defaultfloat;
}

//-----------------------------------------------------------------------------

int main()
try {
    const string path = "./";
    cout << "Введите имя файла для ввода:\n";
    string iname;
    cin >> iname;
    iname = path + iname;
    cout << "Введите имя файла для вывода\n";
    string oname;
    cin >> oname;
    oname = path + oname;

    ifstream ifs{iname};
    if (!ifs)
        error("Невозможно открыть входной файл");
    ifs.exceptions(ifs.exceptions()|ios_base::badbit);

    vector<double> digits;
    fill_vector(ifs, digits, '|', "Неправильное завершение ввода");

    ofstream ofs{oname};
    if (!ofs) error("Невозможно открыть выходной файл: ", iname);
    fill_on_stream(ofs, digits);

    keep_window_open("~~");
    return 0;
}
catch(exception& e) {
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return -1;
}
catch (...) {
    cout << "Неизвестное исключение\n";
    keep_window_open("~");
}

//-----------------------------------------------------------------------------
