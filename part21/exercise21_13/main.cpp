//------------------------------------------------------------------------------

#include "Clear_punctstream.hpp"

//------------------------------------------------------------------------------

void work_with_ps()
{
    const string path{"./"};
    vector<Word_replace> wr_tb;
    init_word_replace(path, wr_tb);
    // Открытие потока istream для бинарного чтения файла
    ifstream ifs {path + "file"};
    if (!ifs) error("Невозможно открыть входной файл!");

    Clear_punctstream ps(ifs);
    ps.whitespace(".;,?-'");
    ps.wordreplace(move(wr_tb));
    ps.case_sensitive(false);
    ps.set_plural(true);

    map<string, int> words; // Поддержка пар (слово, частота)
    for (string s; ps >> s; )
        ++words[s];

    cout << accumulate(words.begin(), words.end(),
                       0, Sum_pair{}) << '\n'
         << words;
}

//------------------------------------------------------------------------------

int main()
try {
    work_with_ps();    
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
