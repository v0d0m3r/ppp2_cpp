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
void fill_vector(istream& ist, vector<string>& words,
                 char term, const string& message)
{
    for (string w; ist >> w; ) words.push_back(w);
    end_of_loop(ist, term, message);
}

//------------------------------------------------------------------------------

void fill_on_stream(ostream& ost, const vector<string>& words)
{
   for (int i=words.size()-1; 0 <= i; --i)
       ost << words[i] << ' ';
}

//------------------------------------------------------------------------------

int main()
try
{
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

    vector<string> words;
    fill_vector(ifs, words, '|', "Неправильное завершение ввода");

    ofstream ofs{oname};
    if (!ofs) error("Невозможно открыть выходной файл: ", iname);
    fill_on_stream(ofs, words);
}
catch (runtime_error& e) {
    cout << e.what() << '\n';
    keep_window_open("~");
}
catch (...) {
    cout << "неизвестное исключение\n";
    keep_window_open("~");
}

//------------------------------------------------------------------------------
