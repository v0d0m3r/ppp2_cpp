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
// Заполняет вектор из потока ввода
void fill_vector(istream& ist, vector<double>& digits,
                 char term, const string& message)
{
    for (double d; ist >> d; )
        digits.push_back(d);
    end_of_loop(ist, term, message);
}

//------------------------------------------------------------------------------
// Сортирует список чисел и находит количество дубликатов
void find_dyplicates(vector<double>& digits, vector<int>& duplicates)
{
    vector<double> temp_digits;
    int duplic = 1;
    for (size_t i=0; i < digits.size(); ++i) {
        if (i == 0)
            temp_digits.push_back(digits[i]);
        else {
            if (digits[i] == digits[i-1])
                    ++duplic;
            else {
                duplicates.push_back(duplic);
                temp_digits.push_back(digits[i]);
                duplic = 1;
            }
        }
        if (i == digits.size()-1)
            duplicates.push_back(duplic);
    }
    digits = temp_digits;
}

//------------------------------------------------------------------------------

void fill_on_stream(ostream& ost, const vector<double>& digits,
                    const vector<int>& duplicates)
{
    for (size_t i=0; i < digits.size(); ++i)
        (duplicates[i] == 1)
            ? ost << digits[i] << '\n'
            : ost << digits[i] << ' '
                  << duplicates[i] << '\n';
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
    vector<int> duplicates;
    sort(digits.begin(), digits.end());
    find_dyplicates(digits, duplicates);

    ofstream ofs{oname};
    if (!ofs) error("Невозможно открыть выходной файл: ", iname);
    fill_on_stream(ofs, digits, duplicates);

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
