//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

void end_of_loop(istream& ist, const string& message)
{
    if (ist.eof()) {
        ist.clear();
        return;
    }
    error("end_of_loop: ", message);
}

//------------------------------------------------------------------------------

void fill_on_file(string& oname, const string& str_file)
{
    ofstream ofs{oname};
    if (!ofs)
        error("Невозможно открыть выходной файл");

    for (int i=str_file.size()-1; 0 <= i; --i)
        ofs << str_file[i];
}

//------------------------------------------------------------------------------
// Создает поток для файла с именем iname
void fill_from_file(string& iname, string& str_file)
{
    ifstream ifs{iname};
    if (!ifs)
        error("Невозможно открыть входной файл");
    ifs.exceptions(ifs.exceptions()|ios_base::badbit);
    for (char ch; ifs.get(ch); ) str_file += ch;
    end_of_loop(ifs, "Неправильное завершение ввода");
}

//------------------------------------------------------------------------------

int main()
try
{
    const string path = "./";
    cout << "Введите имя файла:\n";
    string ioname;
    cin >> ioname;
    ioname = path + ioname;

    string str_file;
    fill_from_file(ioname, str_file);    
    fill_on_file(ioname, str_file);
}
catch (runtime_error& e) {
    cout << e.what() << '\n';
    keep_window_open("~");
}
catch (...) {
    cout << "неизвестная ошибка\n";
    keep_window_open("~");
}

//------------------------------------------------------------------------------
