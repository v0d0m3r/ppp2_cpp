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
void fill_vector(istream& ist, vector<int>& v,
                 char term, const string& message)
{
    int code = 10;
    for (char ch; ist.get(ch);)
        v.push_back(code + int(ch));

    end_of_loop(ist, term, message);
}

//------------------------------------------------------------------------------

void text_to_bynary()
{
    const string path = "./";
    // Открытие потока istream для бинарного чтения файла
    cout << "Введите имя файла для ввода\n";
    string iname;
    cin >> iname;
    iname = path + iname;
    ifstream ifs{iname};
    if (!ifs)
        error("Невозможно открыть входной файл");
    ifs.exceptions(ifs.exceptions()|ios_base::badbit);

    vector<int> v;
    fill_vector(ifs, v, '|', "Неправильное завершение ввода");

    cout << "Введите имя файла для вывода\n";
    string oname;
    cin >> oname;
    oname = path + oname;
    ofstream ofs{oname, ios_base::binary};
    if (!ofs) error("Невозможно открыть выходной файл: ", oname);
    for (int& i : v)
        ofs.write(as_bytes(i), sizeof(int));
}

//------------------------------------------------------------------------------

void bynary_to_text()
{
    const string path = "./";
    // Открытие потока istream для бинарного чтения файла
    cout << "Введите имя файла для ввода\n";
    string iname;
    cin >> iname;
    iname = path + iname;
    ifstream ifs {iname, ios_base::binary};
    if (!ifs) error("Невозможно открыть входной файл: ", iname);
    // Открытие потока ostream для бинарной записи файла
    cout << "Введите имя файла для вывода\n";
    string oname;
    cin >> oname;
    oname = path + oname;
    ofstream ofs{oname};
    if (!ofs) error("Невозможно открыть выходной файл: ", iname);

    // Чтение из бинарного файла
    string text;
    for (int x; ifs.read(as_bytes(x), sizeof(int));) {  // Чтение
        x-=10;                                          // байт
        text += char(x);
    }   

    // Запись в бинарный файл
    ofs << text;
}

//------------------------------------------------------------------------------

int main()
try {
    //text_to_bynary();
    bynary_to_text();
    keep_window_open("~~");
    return 0;
}
catch(exception& e) {
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return -1;
}

//------------------------------------------------------------------------------
