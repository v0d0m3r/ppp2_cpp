//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//-----------------------------------------------------------------------------

enum class Category {
    start, space, alpha, digit, xdigit,
    upper, lower, alnum, cntrl,
    punct, print, graph, finish
};

//-----------------------------------------------------------------------------

vector<string> name_category_tb {
    "start", "space", "alpha", "digit", "xdigit",
    "upper", "lower", "alnum", "cntrl",
    "punct", "print", "graph", "finish"
};

//-----------------------------------------------------------------------------

struct Symb_categories {
    char ch;
    vector<Category> categ_tb;
};

//-----------------------------------------------------------------------------

ostream& operator<<(ostream& ost, const Symb_categories& sc)
{
    ost << '\"' << sc.ch << '\"' << ' '
        << "Категории (";
    for (size_t i=0; i < sc.categ_tb.size(); ++i) {
        ost << name_category_tb[int(sc.categ_tb[i])];
        if (i != sc.categ_tb.size()-1)
            ost << ", ";
        else
            ost << ")\n";
    }
    return ost;
}

//-----------------------------------------------------------------------------

Category get_category(const char& ch, const Category& current)
{
    static const pair<string, string> err_msg{"get_category: ",
                                              "неизвестная категория"};
    switch (current) {
    case Category::start:
        if (isprint(ch)) return Category::print;
        else if (iscntrl(ch)) return Category::cntrl;
        else error(err_msg.first, err_msg.second);
    case Category::cntrl: case Category::space:
    case Category::punct: case Category::digit:
    case Category::upper: case Category::lower:
        return Category::finish;
    case Category::print:
        if (isgraph(ch)) return Category::graph;
        else if (isspace(ch)) return Category::space;
        else error(err_msg.first, err_msg.second);
    case Category::graph:
        if (isalnum(ch)) return Category::alnum;
        else if (ispunct(ch)) return Category::punct;
        else error(err_msg.first, err_msg.second);
    case Category::alnum:
        if (isxdigit(ch)) return Category::xdigit;
        else if (isalpha(ch)) return Category::alpha;
        else error(err_msg.first, err_msg.second);
    case Category::xdigit:
        if (isdigit(ch)) return Category::digit;
        else if (isalpha(ch)) return Category::alpha;
        else error(err_msg.first, err_msg.second);
    case Category::alpha:
        if (isupper(ch)) return Category::upper;
        else if (islower(ch)) return Category::lower;
        else error(err_msg.first, err_msg.second);
    default:
        error(err_msg.first, err_msg.second);
    }
}

//------------------------------------------------------------------------------

void all_categories(Symb_categories& sc)
{
    Category category = get_category(sc.ch, Category::start);
    while (category != Category::finish) {
        sc.categ_tb.push_back(category);
        category = get_category(sc.ch, category);
    }
}

//------------------------------------------------------------------------------

void str_parser(const string& line, vector<Symb_categories>& sc_tb)
{
    Symb_categories sc;
    for (const auto& ch : line) {
        sc = Symb_categories{};
        sc.ch = ch;
        all_categories(sc);
        sc_tb.push_back(sc);
    }
}

//------------------------------------------------------------------------------

void end_of_loop(istream& ist, const string& message)
{
    if (ist.eof()) {        // Конец файла
        ist.clear();
        return;
    }
    error("end_of_loop: ", message);
}

//------------------------------------------------------------------------------
// Создает поток для файла с именем iname
void fill_from_stream(istream& ist, vector<Symb_categories>& sc_tb)
{
    ist.exceptions(ist.exceptions()|ios_base::badbit);

    for (string line; getline(ist, line);)
        str_parser(line, sc_tb);

    end_of_loop(ist, "Неправильное завершение ввода");
}

//------------------------------------------------------------------------------

void fill_on_stream(ostream& ost, const vector<Symb_categories>& sc_tb)
{
    ost << '\n';
    for (const auto& sc : sc_tb) ost << sc;
}

//-----------------------------------------------------------------------------

void symb_analyzer()
{
    const string path = "./";
    cout << "Введите имя файла:\n";
    string iname;
    cin >> iname;
    iname = path + iname;
    ifstream ifs{iname};
    if (!ifs)
        error("Невозможно открыть входной файл");

    vector<Symb_categories> sc_tb;
    fill_from_stream(ifs, sc_tb);
    fill_on_stream(cout, sc_tb);
}

//-----------------------------------------------------------------------------

int main()
try {
    symb_analyzer();
    keep_window_open("~~");
    return 0;
}
catch(exception& e) {
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return -1;
}

//-----------------------------------------------------------------------------
