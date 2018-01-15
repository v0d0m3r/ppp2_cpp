//------------------------------------------------------------------------------

#include "Clear_punctstream.hpp"

//------------------------------------------------------------------------------

void end_of_loop(istream& ist, char term, const string& message)
{
    if (ist.eof()) {
        ist.clear();
        return;
    }
    if (ist.fail()) {
        ist.clear();
        char c;
        if (ist >> c && c==term) return;
        error("end_of_loop: ", message);
    }
}

//------------------------------------------------------------------------------

void init_word_replace(const string& path, vector<Word_replace>& wr_tb)
{
    cout << "Введите имя файла для ввода "
         << "списка слов для замены\n";
    string iname;
    cin >> iname;
    iname = path + iname;
    ifstream ifs {iname};
    if (!ifs) error("Невозможно открыть входной файл: ", iname);
    ifs.exceptions(ifs.exceptions()|ios_base::badbit);
    for (Word_replace wr; ifs >> wr;)
        wr_tb.push_back(wr);

    end_of_loop(ifs, '*', "Некорректный ввод");
}

//------------------------------------------------------------------------------

template<typename A, typename B>
std::ostream& operator<<(std::ostream& os, const std::pair<A, B>& p)
{
    return os << '(' << p.first << ',' << p.second << ')';
}

//------------------------------------------------------------------------------

template<typename A, typename B>
std::ostream& operator<<(std::ostream& os, const map<A, B>& m)
{
    for (const auto& p : m) os << p << '\n';
    return os;
}

//------------------------------------------------------------------------------

void work_with_ps()
{
    const string path = "./";
    vector<Word_replace> wr_tb;
    init_word_replace(path, wr_tb);
    // Открытие потока istream для бинарного чтения файла
    cout << "Введите имя файла для ввода\n";
    string iname;
    cin >> iname;
    iname = path + iname;
    ifstream ifs {iname};
    if (!ifs) error("Невозможно открыть входной файл: ", iname);

    Clear_punctstream ps(ifs);
    ps.whitespace(".;,?-'");
    ps.wordreplace(move(wr_tb));
    ps.case_sensitive(false);

    map<string, int> words; // Поддержка пар (слово, частота)
    for (string s; ps >> s; )
        ++words[s];

    cout << words;
}

//------------------------------------------------------------------------------

int main()
try {
    work_with_ps();
    keep_window_open("~~");
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
