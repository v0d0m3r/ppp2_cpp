//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

void fill_on_file(const vector<string>& data_tb, const string& oname)
{
    ofstream ost {oname};    // Поток для записи в файл
    if (!ost) error("невозможно открыть файл: ", oname);
    for (const string& d : data_tb)
        ost << d << ' ';
}

//------------------------------------------------------------------------------

void end_of_loop(ifstream& ist, char term, const string& message)
{
    if (ist.eof()) {        // Конец файла
        ist.clear();
        return;
    }
    ist.clear();
    char c;
    if (ist >> c && c==term) return;
    error("end_of_loop: ", message);
}

//------------------------------------------------------------------------------

void str_tolower(string& s)
{
    for (char& c : s) c = tolower(c);
}

//------------------------------------------------------------------------------
// Создает поток для файла с именем iname
// и записывает данные в нижнем регистре в data_tb
void fill_from_file(vector<string>& data_tb, const string& iname)
{
    ifstream ist{iname};
    if (!ist)
        error("temp_stats: ", "Невозможно открыть входной файл");
    ist.exceptions(ist.exceptions()|ios_base::badbit);

    char term = '*';    // Символ прекращения ввода
    for (string d; ist >> d;)
        data_tb.push_back(d);

    end_of_loop(ist, term, "Неправильное завершение файла");
}

//------------------------------------------------------------------------------

void file_tolower()
try
{
    const string path = "./";
    string iname;
    string oname;
    cout << "Введите имя входного файла: " << '\n';
    cin >> iname;

    cout << "Введите имя выходного файла: " << '\n';
    cin >> oname;
    iname = path + iname;
    oname = path + oname;

    vector<string> data_tb;
    fill_from_file(data_tb, iname);    // Ввод из файла

    for (string& d : data_tb)
        str_tolower(d);

    fill_on_file(data_tb, oname);      // Вывод в файл результат
}
catch (exception& e) {
    cerr << "ошибка: " << e.what() << '\n';
}
catch (...) {
    cerr << "Неизвестная ошибка!\n";
}


//------------------------------------------------------------------------------

int main()
{
    file_tolower();
    keep_window_open("~~");
    return 0;
}

//------------------------------------------------------------------------------
