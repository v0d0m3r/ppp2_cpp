//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

struct Find_line {
    vector<string> line_tb;
    string word;
    vector<int> num_line_tb;
};

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

bool word_in_line(const string& word, const string& line)
{
    istringstream is{line};
    is.exceptions(is.exceptions()|ios_base::badbit);

    for (string str; is >> str;)
        if (word == str) return true;
    return false;
}

//------------------------------------------------------------------------------
// Создает поток для файла с именем iname
// и записывает данные в нижнем регистре в data_tb
void find_line_from_file(Find_line& fl, const string& iname)
{
    ifstream ifs{iname};
    if (!ifs)
        error("temp_stats: ", "Невозможно открыть входной файл");
    ifs.exceptions(ifs.exceptions()|ios_base::badbit);

    char term = '*';    // Символ прекращения ввода
    int counter = 0;
    for (string line; getline(ifs, line);) {
        if (word_in_line(fl.word, line)) {
            fl.line_tb.push_back(line);
            fl.num_line_tb.push_back(counter);
        }
        ++counter;
    }
    end_of_loop(ifs, term, "Неправильное завершение файла");
}

//------------------------------------------------------------------------------

void print_find_line(const Find_line& fl)
{
    if (fl.line_tb.size() != fl.num_line_tb.size())
        error("Не сходятся размеры массивов");

    if (fl.line_tb.size() == 0) {
        cout << "Нет совпадений со словом: "
             << fl.word << '\n';
        return;
    }
    cout << "Слово `" << fl.word
         << "` найдено:\n";
    for (size_t i=0; i < fl.line_tb.size(); ++i)
        cout << fl.num_line_tb[i] << " - "
             << fl.line_tb[i] << ";\n";

}

//------------------------------------------------------------------------------

void finder()
try
{
    const string path = "./";
    string iname;
    cout << "Введите имя входного файла: " << '\n';
    cin >> iname;
    iname = path + iname;

    string word;
    cout << "Введите слово, для поиска в файле: " << '\n';
    cin >> word;

    Find_line fl;
    fl.word = word;
    find_line_from_file(fl, iname);    // Ввод из файла
    print_find_line(fl);
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
    finder();
    keep_window_open("~~");
    return 0;
}

//------------------------------------------------------------------------------
