//------------------------------------------------------------------------------

#include "vowelstream.hpp"

//------------------------------------------------------------------------------

void fill_on_file(const vector<string>& data_tb, const string& oname)
{
    ofstream ost {oname};    // Поток для записи в файл
    if (!ost) error("невозможно открыть файл: ", oname);
    for (const string& d : data_tb)
        ost << d << ' ';
}

//------------------------------------------------------------------------------
// Создает поток для файла с именем iname
// и считывает слова без глассных букв
void fill_from_file(vector<string>& data_tb, const string& iname)
{
    ifstream ist{iname};
    if (!ist)
        error("Невозможно открыть входной файл");
    ist.exceptions(ist.exceptions()|ios_base::badbit);

    Vowel_stream vs(ist);
    vs.vowel_symb("AaEeIiOoUu");
    vs.case_sensitive(false);

    for (string word; vs >> word;)
        data_tb.push_back(word);
}

//------------------------------------------------------------------------------

void witout_vowel()
{
    const string path = "./";
    // Открытие потока istream для бинарного чтения файла
    cout << "Введите имя файла:\n";
    string iname;
    cin >> iname;
    iname = path + iname;
    vector<string> data_tb;
    fill_from_file(data_tb, iname);    // Ввод из файла
    fill_on_file(data_tb, iname);      // Вывод в файл результат
}

//------------------------------------------------------------------------------

int main()
{
    try {
        witout_vowel();
    }
    catch(exception& e) {
        cerr << e.what() << '\n';
        keep_window_open("~~");
        return -1;
    }
    keep_window_open("~~");
    return 0;
}

//------------------------------------------------------------------------------
