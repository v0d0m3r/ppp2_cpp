//------------------------------------------------------------------------------

#include "punctstream.hpp"

//------------------------------------------------------------------------------

void work_with_ps()
{
    const string path = "./";
    // Открытие потока istream для бинарного чтения файла
    cout << "Введите имя файла для ввода\n";
    string iname;
    cin >> iname;
    iname = path + iname;
    ifstream ifs {iname};
    if (!ifs) error("Невозможно открыть входной файл: ", iname);

    Punct_stream ps(ifs);
    //Punct_stream ps(cin);
    ps.whitespace(".;,?-'");
    Word_replace wr;
    wr.short_form = "don't";
    wr.full_form = "do not";
    ps.add_wordreplace(wr);
    ps.case_sensitive(false);
    vector<string> vs;
    for (string word; ps >> word;)
        vs.push_back(word);         // Ввод слов

    for (size_t i=0; i <vs.size(); ++i)
        cout << vs[i] << '\n';
    cout << '\n';
}

//------------------------------------------------------------------------------

int main()
try {
    work_with_ps();
    keep_window_open("~~");
    return 0;
}
catch(exception& e) {
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return -1;
}

//------------------------------------------------------------------------------
